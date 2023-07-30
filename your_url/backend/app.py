from flask import Flask, jsonify, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
from flask_cors import CORS  # Import the CORS module

app = Flask(__name__)
CORS(app) 
app.config['SECRET_KEY'] = 'your_secret_key'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mydatabase.db'
db = SQLAlchemy(app)

def delete_all_data():
    try:
        db.session.query(Redirect).delete()
        db.session.commit()
        print("All data deleted successfully.")
    except Exception as e:
        db.session.rollback()
        print("Error deleting data:", e)


class Redirect(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    old_url = db.Column(db.String(50))
    your_url = db.Column(db.String(50))

    def __init__(self, old_url, your_url):
        self.old_url = old_url
        self.your_url = your_url

@app.route('/')
def home():
    return 'Hello, Flask!!'

@app.route('/redirections', methods=['GET'])
def api_redirects():
    redirections_data = Redirect.query.all()
    redirections = [{'id': r.id, 'old_url': r.old_url, 'your_url': r.your_url} for r in redirections_data]
    return jsonify(redirections)

@app.route('/redirections/add', methods=['GET', 'POST'])
def api_add_redirection():
    # Your code to handle GET and POST requests here
    if request.method == 'POST':
        # Handle the POST request to add a redirection
        data = request.get_json()
        old_url = data.get('old_url')
        your_url = data.get('your_url')

        redirection = Redirect(old_url, your_url)
        db.session.add(redirection)
        db.session.commit()
        
        new_redirection = Redirect.query.filter_by(old_url=old_url, your_url=your_url).first()
        return jsonify({'message': 'Redirect added successfully', 'new_url': new_redirection.your_url})
    
    elif request.method == 'GET':
        # Handle the GET request to fetch redirection data (if needed)
        # ...

        return jsonify({'message': 'This is a GET request'})

    else:
        # Return a 405 Method Not Allowed for any other request methods
        return jsonify({'error': 'Method Not Allowed'}), 405


@app.errorhandler(404)
def page_not_found(error):
    redirects_with_specific_url = Redirect.query.filter_by(your_url=request.path[1:]).all()
    if redirects_with_specific_url:
        old_url = redirects_with_specific_url[0].old_url
        return redirect(old_url)
    else:
        return error

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)
