import os
from selenium import webdriver

# initialize the webdriver
driver = webdriver.Firefox()

# Navigate to the ChatGPT API endpoint
driver.get("https://api.openai.com/v1/engines/davinci-codex/completions")

# Enter the api_key
driver.find_element_by_name("api_key").send_keys( os.getenv("OPENAI_API_KEY") )

# Call to prompt
driver.find_element_by_name("prompt").send_keys("What is the meaning of life?")

# Submit the query form
driver.find_element_by_xpath("//input[@type'submit']").click()

# Response
print( driver.find_element_by_xpath("//pre").text )

# Shutdown
driver.close()