from sentence_transformers import SentenceTransformer
import json
import numpy as np

model = SentenceTransformer("sentence-transformers/all-MiniLM-L6-v2")

with open("../functions.json", "r", encoding="utf-8") as f:
    functions = json.load(f)

texts = []

for func in functions:
    text = (
        f"Function: {func['name']}\n"
        f"File: {func['file']}\n\n"
        f"{func['code']}"
    )
    texts.append(text)

print(f"Generating embeddings for {len(texts)} functions...")

embeddings = model.encode(
    texts,
    batch_size=32,
    show_progress_bar=True,
    convert_to_numpy=True,
    normalize_embeddings=True
)

embeddings.astype(np.float32).tofile("../embeddings.bin")

print("Saved embeddings.bin")