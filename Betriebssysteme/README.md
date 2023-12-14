# E-mail Analysis Script
The email_analysis.sh script is a versatile tool designed for parsing email files and providing insights into sender activities and the prevalence of email service providers. 
This script is particularly useful for analyzing datasets to identify patterns, such as the most prolific senders and frequently occurring email providers.

# How to Use
To use the script, run the following command in your terminal:

- ./email_analysis.sh [-h|--help] | [-e|--email] | [-c|--company] + [filename]

### Options
- -h|--help: Display help information and exit.
- -e|--email: Extract and display a sorted list of unique email addresses found in the specified file.
- -c|--company: Extract and display email providers along with the number of occurrences in the specified file.
  
### How It Works
The script parses the provided email file and identifies sender information, allowing users to understand the distribution of emails. It includes functionality to:

### Extract and Display Email Addresses
- ./email_analysis.sh -e emails.txt
This command outputs a sorted list of unique email addresses found in the specified emails.txt file.

### Extract and Display Email Providers
- ./email_analysis.sh -c emails.txt
This command outputs a list of email providers along with the number of occurrences found in the specified emails.txt file.

# Notes
If no option is specified, the script defaults to -e (email extraction) to provide a comprehensive list of unique email addresses.
In case the script is executed without a valid filename or with an incorrect option, it will display an error message along with the help information.
Feel free to customize the script according to your specific dataset and requirements. 
This tool can be invaluable for gaining insights into email communication patterns and identifying influential senders or prevalent email service providers.
