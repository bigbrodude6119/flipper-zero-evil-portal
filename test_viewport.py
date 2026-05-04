import os
import re

PORTALS_DIR = 'portals'

for root, dirs, files in os.walk(PORTALS_DIR):
    for filename in files:
        if filename.endswith('.html'):
            filepath = os.path.join(root, filename)
            with open(filepath, 'r', encoding='utf-8') as f:
                content = f.read()

            if not re.search(r'<meta[^>]*name\s*=\s*["\']viewport["\']', content, re.IGNORECASE):
                print(f"Missing viewport meta in {filepath}")
