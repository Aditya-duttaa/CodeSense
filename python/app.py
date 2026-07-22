from flask import Flask, request, render_template_string
import subprocess
import json

app = Flask(__name__)

HTML = """
<!doctype html>
<html>
<head>
    <title>CodeSense</title>
    <style>
        body{
            font-family:Arial;
            margin:40px;
            background:#f4f4f4;
        }
        input{
            width:500px;
            padding:10px;
            font-size:16px;
        }
        button{
            padding:10px 20px;
            font-size:16px;
        }
        .card{
            background:white;
            padding:15px;
            margin-top:20px;
            border-radius:8px;
            box-shadow:0 0 5px rgba(0,0,0,.2);
        }
        pre{
            background:#272822;
            color:#f8f8f2;
            padding:10px;
            overflow:auto;
        }
    </style>
</head>

<body>

<h1>CodeSense</h1>

<form method="POST">
    <input
        name="query"
        placeholder="Search..."
        value="{{query}}">

    <button type="submit">
        Search
    </button>
</form>

{% for r in results %}

<div class="card">

<h2>{{r.name}}</h2>

<b>File:</b> {{r.file}} <br>
<b>Score:</b> {{ "%.4f"|format(r.score) }}

<pre>{{r.code}}</pre>

</div>

{% endfor %}

</body>
</html>
"""

@app.route("/", methods=["GET","POST"])
def home():

    results=[]

    query=""

    if request.method=="POST":

        query=request.form["query"]

        subprocess.run(
            [
                "python",
                "query_embed.py",
                query
            ],
            cwd="."
        )

        output=subprocess.check_output(
            [
                "../build/CodeSense.exe",
                "--json"
            ],
            cwd="."
        )

        results=json.loads(output)

    return render_template_string(
        HTML,
        results=results,
        query=query
    )

app.run(debug=True)