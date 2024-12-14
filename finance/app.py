import os
import cs50
import sqlite3

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Verifique se o símbolo está preenchido e se shares é um inteiro positivo
        if not symbol or not shares.isdigit() or int(shares) <= 0:
            flash("Entrada inválida. Por favor, preencha os campos corretamente.")
            return redirect("/buy")

        price_data = lookup(symbol)  # Obter o preço atual da ação
        if price_data is None:
            flash("Símbolo inválido.")
            return redirect("/buy")

        price = price_data['price']  # Supondo que a função lookup retorna um dicionário com a chave 'price'
        user_balance = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']

        # Verifique se o usuário tem saldo suficiente
        total_cost = price * int(shares)
        if user_balance < total_cost:
            flash("Saldo insuficiente para completar a compra.")
            return redirect("/buy")

        # Registrar a compra na tabela transactions
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session['user_id'], symbol, int(shares), price)

        # Atualizar o saldo do usuário
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session['user_id'])

        flash("Compra realizada com sucesso!")
        return redirect("/")

    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Query database for username & transactions
    user_transactions = db.execute(
        "SELECT id, symbol, shares, price, transacted  FROM transactions WHERE id = ? ORDER BY transacted", session["user_id"])

    return render_template("history.html", user_transactions=user_transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


from flask import session, redirect, url_for

@app.route("/logout")
def logout():
    # Remove o usuário da sessão
    session.clear()
    return redirect(url_for("index"))


@app.route("/quote", methods=["GET", "POST"])
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        price_data = lookup(symbol)  # Suponha que lookup retorna None se o símbolo não for encontrado

        # Verifique se o símbolo é válido
        if not symbol or price_data is None:
            flash("Símbolo inválido.")
            return redirect("/quote")

        # Extraia o preço da resposta da função lookup
        price = price_data["price"]  # Supondo que lookup retorna um dicionário com a chave 'price'

        return render_template("quoted.html", symbol=symbol, price=price)

    return render_template("quoted.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validação
        if not username or not password or not confirmation:
            flash("Deve preencher todos os campos.")
            return redirect("/register")

        if password != confirmation:
            flash("As senhas não correspondem.")
            return redirect("/register")

        # Verifique se o nome de usuário já existe
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if existing_user:
            flash("Nome de usuário já existe.")
            return redirect("/register")

        # Inserir no banco de dados
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, generate_password_hash(password))

        return redirect("/login")

    return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Verifique se o símbolo está selecionado
        if not symbol:
            flash("Por favor, selecione uma ação.")
            return redirect("/sell")

        # Verifique se o número de ações é um inteiro positivo
        if not shares.isdigit() or int(shares) <= 0:
            flash("Número de ações inválido. Deve ser um inteiro positivo.")
            return redirect("/sell")

        shares = int(shares)

        # Verifique se o usuário possui ações suficientes
        user_id = session["user_id"]
        user_shares = db.execute("""
            SELECT SUM(shares) AS total_shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
        """, user_id, symbol)

        if not user_shares or user_shares[0]["total_shares"] < shares:
            flash("Você não possui ações suficientes para vender.")
            return redirect("/sell")

        # Registrar a venda na tabela transactions
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   user_id, symbol, -shares, lookup(symbol)["price"])

        flash("Venda realizada com sucesso!")
        return redirect("/")

    # Se for um GET, exiba o formulário com as ações que o usuário possui
    user_id = session["user_id"]
    stocks = db.execute("""
        SELECT symbol, SUM(shares) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
    """, user_id)

    return render_template("sell.html", stocks=stocks)

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        if not new_password or new_password != confirmation:
            flash("As senhas não correspondem ou estão vazias.")
            return redirect("/change_password")

        # Atualizar a senha no banco de dados
        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_password), session['user_id'])
        flash("Senha alterada com sucesso!")
        return redirect("/")

    return render_template("change_password.html")

@app.route("/")
@login_required
def index():
    user_id = session["user_id"]

    # Obter as ações do usuário, somando as ações por símbolo
    user_stocks = db.execute("""
        SELECT symbol, SUM(shares) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
    """, user_id)

    total_value = 0
    stocks_with_prices = []

    # Para cada ação, obtenha o preço atual e calcule o valor total
    for stock in user_stocks:
        lookup_result = lookup(stock["symbol"])  # Obter o preço atual
        if lookup_result:
            price = lookup_result["price"]
            total_shares = stock["total_shares"]
            total_stock_value = price * total_shares
            total_value += total_stock_value  # Acumulando o valor total das ações
            stocks_with_prices.append({
                "symbol": stock["symbol"],
                "total_shares": total_shares,
                "price": price,
                "total_value": total_stock_value
            })

    # Obter o saldo de caixa do usuário
    user_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Calcular o valor total (ações + saldo)
    total_value += user_balance

    return render_template("index.html", stocks=stocks_with_prices, balance=user_balance, total_value=total_value)
