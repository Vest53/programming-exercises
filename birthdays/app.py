import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
import sqlite3
app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('birthdays.db')
    conn.row_factory = sqlite3.Row  # Para acessar as colunas pelo nome
    return conn

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Validação de dados
        if not name or not month or not day:
            return redirect("/")

        try:
            month = int(month)
            day = int(day)
            if month < 1 or month > 12 or day < 1 or day > 31:
                return redirect("/")
        except ValueError:
            return redirect("/")

        # Adicionar ao banco de dados
        conn = get_db_connection()
        conn.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", (name, month, day))
        conn.commit()
        conn.close()
        return redirect("/")  # Redireciona para a página principal

    # Consultar todos os aniversários
    conn = get_db_connection()
    birthdays = conn.execute("SELECT * FROM birthdays").fetchall()
    conn.close()
    return render_template("index.html", birthdays=birthdays)

if __name__ == "__main__":
    app.run(debug=True)
