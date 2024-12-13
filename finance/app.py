import os

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
    # Lógica para obter ações e saldo do usuário
    # Exemplo: user_stocks = get_user_stocks(user_id)

    return render_template("index.html", stocks=user_stocks, balance=user_balance)


@app.route("/buy", methods=["GET", "POST"])
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validação
        if not symbol or not shares.isdigit() or int(shares) <= 0:
            flash("Entrada inválida.")
            return redirect("/buy")

        # Lógica para procurar o preço atual e verificar saldo
        # Exemplo: price = lookup(symbol)

        if not price or user_balance < price * int(shares):
            flash("Saldo insuficiente.")
            return redirect("/buy")

        # Inserir a compra no banco de dados
        cs50.SQL("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                  user_id, symbol, shares, price)

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
def history():
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
            cs50.SQL("INSERT INTO users (username, hash) VALUES (?, ?)",
                      username, generate_password_hash(password))
        except cs50.SQL.IntegrityError:
            flash("Nome de usuário já existe.")
            return redirect("/register")

        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
def sell():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validação
        if not symbol or not shares.isdigit() or int(shares) <= 0:
            flash("Entrada inválida.")
            return redirect("/sell")

        # Lógica para verificar se o usuário possui ações
        # Exemplo: user_shares = get_user_shares(user_id, symbol)

        if user_shares < int(shares):
            flash("Você não possui ações suficientes.")
            return redirect("/sell")

        # Inserir a venda no banco de dados
        cs50.SQL("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                  user_id, symbol, -int(shares), price)

        return redirect("/")

    return render_template("sell.html")
