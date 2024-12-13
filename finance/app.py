import os
import cs50
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


@app.route("/")
def index():
    # Garantir que o usuário esteja autenticado
    if 'user_id' not in session:
        return redirect(url_for("login"))

    user_id = session['user_id']

    # Obter o saldo do usuário
    user_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

    # Obter ações do usuário
    user_stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

    # Para cada ação, obter o preço atual
    stocks_with_prices = []
    for stock in user_stocks:
        symbol = stock['symbol']
        total_shares = stock['total_shares']
        price = lookup(symbol)  # Função que busca o preço da ação
        stocks_with_prices.append({
            'symbol': symbol,
            'total_shares': total_shares,
            'price': price,
            'total_value': total_shares * price  # Valor total das ações
        })

    return render_template("login.html", stocks=stocks_with_prices, balance=user_balance)


@app.route("/buy", methods=["GET", "POST"])
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares.isdigit() or int(shares) <= 0:
            flash("Entrada inválida.")
            return redirect("/buy")

        price = lookup(symbol)  # Obter o preço atual da ação
        user_balance = cs50.SQL("SELECT cash FROM users WHERE id = ?", session['user_id'])[0]['cash']

        if price is None or user_balance < price * int(shares):
            flash("Saldo insuficiente ou símbolo inválido.")
            return redirect("/buy")

        cs50.SQL("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                  session['user_id'], symbol, int(shares), price)

        return redirect("/")

    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    user_id = session['user_id']
    transactions = cs50.SQL("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)

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
        # Lógica para buscar o preço da ação
        # Exemplo: price = lookup(symbol)

        if not symbol or not price:
            flash("Símbolo inválido.")
            return redirect("/quote")

        return render_template("quoted.html", symbol=symbol, price=price)

    return render_template("quote.html")


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

        # Inserir no banco de dados
        try:
            db = cs50.SQL("sqlite:///finance.db")  # Conecte-se ao banco de dados
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
        except sqlite3.IntegrityError:
            flash("Nome de usuário já existe.")
            return redirect("/register")

        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares.isdigit() or int(shares) <= 0:
            flash("Entrada inválida.")
            return redirect("/sell")

        user_id = session['user_id']
        user_shares = cs50.SQL("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]['SUM(shares)'] or 0

        if user_shares < int(shares):
            flash("Você não possui ações suficientes.")
            return redirect("/sell")

        price = lookup(symbol)
        cs50.SQL("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                  user_id, symbol, -int(shares), price)

        return redirect("/")

    return render_template("sell.html")
