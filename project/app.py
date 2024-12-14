from flask import Flask, render_template, request, redirect
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'
db = SQLAlchemy(app)

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
