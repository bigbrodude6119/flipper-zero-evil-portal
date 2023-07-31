from bs4 import BeautifulSoup
import requests
import os
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
import time
import sys
from urllib.parse import urljoin, urlparse
import re
import shutil
import platform

def get_chromedriver_path():
    if platform.system() == "Windows":
        return "chromedriver.exe"
    else:
        return "./chromedriver"  

def clean_filename(filename):
    return re.sub(r'[\\/*?:"<>|]', '_', filename)  # replace invalid characters with an underscore

def download_file(url, path):
    local_filename = clean_filename(url.split('/')[-1])
    try:
        r = requests.get(url, stream=True)
        r.raise_for_status()
        with open(os.path.join(path, local_filename), 'wb') as f:
            for chunk in r.iter_content(chunk_size=8192): 
                if chunk:  # filter out keep-alive new chunks
                    f.write(chunk)
        print(f"Downloaded {url} successfully.")
    except requests.exceptions.RequestException as err:
        print(f"Error occurred while downloading {url}: {err}")
        return None
    return local_filename

def get_directory_name(path):
    count = 1
    new_path = path
    while os.path.exists(new_path):
        new_path = f"{path}({count})"
        count += 1
    return new_path

def remove_cookie_popup(soup):
    # Find elements with 'truste-consent-track' in id
    cookie_elements = soup.find_all(id='truste-consent-track')

    # Remove all found elements
    for element in cookie_elements:
        element.decompose()

def main(url):
    options = webdriver.ChromeOptions()
    options.add_argument('--ignore-certificate-errors')
    options.add_argument('--incognito')
    options.add_argument('--headless')
    
    service = Service(get_chromedriver_path())
    driver = webdriver.Chrome(service=service, options=options)

    driver.get(url)
    time.sleep(3)

    html = driver.page_source

    soup = BeautifulSoup(html, 'html.parser')

    remove_cookie_popup(soup)

    website_directory = urlparse(url).hostname  # Use hostname as directory name
    path = os.path.join(os.getcwd(), website_directory)
    
    if os.path.exists(path):
        response = input(f"Directory {path} already exists. Overwrite? (y/n): ")
        if response.lower() != 'y':
            path = get_directory_name(path)
        else:
            try:
                shutil.rmtree(path, ignore_errors=False)  # Remove the existing directory
            except PermissionError:
                print("The directory is currently in use. Creating a new directory...")
                path = get_directory_name(path)

    try:
        os.makedirs(path, exist_ok=True)
    except Exception as e:
        print(f"Error occurred while creating directory {path}: {e}")

    for link in soup.find_all('link'):
        href = link.get('href')
        if href and not href.startswith(('data:', 'javascript:', 'mailto:', 'http:', 'https:', '#')):
            file_url = urljoin(url, href)
            link['href'] = file_url
            file_path = download_file(file_url, path)
            if file_path is not None:
                link['href'] = file_path

    for script in soup.find_all('script'):
        src = script.get('src')
        if src and not src.startswith(('data:', 'javascript:', 'mailto:', 'http:', 'https:', '#')):
            file_url = urljoin(url, src)
            script['src'] = file_url
            file_path = download_file(file_url, path)
            if file_path is not None:
                script['src'] = file_path

    for img in soup.find_all('img'):
        src = img.get('src')
        if src and not src.startswith(('data:', 'javascript:', 'mailto:', 'http:', 'https:', '#')):
            file_url = urljoin(url, src)
            img['src'] = file_url
            file_path = download_file(file_url, path)
            if file_path is not None:
                img['src'] = file_path

    for script in soup.find_all('script'):
        script.decompose()

    try:
        index_path = os.path.join(path, 'index.html')
        with open(index_path, 'w', encoding='utf-8') as file:
            file.write(str(soup))
        print(f"\nAll tasks completed successfully. Everything has been added to the directory: {path}")
    except Exception as e:
        print(f"Error occurred while creating index.html: {e}")

if __name__ == "__main__":
    main(sys.argv[1])
