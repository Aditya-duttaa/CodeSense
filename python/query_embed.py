from sentence_transformers import SentenceTransformer
import numpy as np
import sys

model = SentenceTransformer("sentence-transformers/all-MiniLM-L6-v2")

query = " ".join(sys.argv[1:])

embedding = model.encode(
    query,
    normalize_embeddings=True,
    convert_to_numpy=True
).astype(np.float32)

embedding.tofile("../query.bin")

print("Saved query.bin")