from flask import session, redirect, url_for
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
db = SQL("sqlite:///donation.db")

class Donation(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    amount = db.Column(db.Float, nullable=False)
    user_id = db.Column(db.Integer, nullable=False)

@app.route("/donate", methods=["GET", "POST"])
def donate():
    if request.method == "POST":
        amount = request.form.get("amount")
        user_id = request.form.get("user_id")  # Obtenha o ID do usuário logado
        new_donation = Donation(amount=amount, user_id=user_id)
        db.session.add(new_donation)
        db.session.commit()
        return redirect("/")
    return render_template("donate.html")
