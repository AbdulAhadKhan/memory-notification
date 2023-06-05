# Auto Notification - Memory Usage by Processes

The **Auto Notification - Memory Usage by Processes** project aims to develop a bash script that continuously monitors the memory allocated to various processes during runtime. The script sends email notifications to network administrators when the memory allotment to a process exceeds a predefined threshold. This automated solution helps system administrators identify and address excessive memory usage, ensuring optimal system performance.

## Features

- Continuous monitoring of memory usage by processes.
- Real-time notifications via email when memory thresholds are exceeded.
- Customizable memory thresholds for individual processes.
- Lightweight and efficient implementation using bash scripting and Linux system calls.

## Prerequisites

- C programming knowledge.
- Familiarity with Linux system calls.
- Proficiency in bash scripting.
- Linux operating system.

## Usage

1. Clone the repository to your local machine.
2. Open the bash script file (`monitor_memory.sh`) in a text editor.
3. Customize the script as needed:
   - Set the desired memory threshold for each process in the `THRESHOLDS` array.
   - Configure the email settings (SMTP server, sender, recipient, etc.) in the `send_email_notification` function.
4. Save the modifications.
5. Run the script using the following command:


## Future Scope

The **Auto Notification - Memory Usage by Processes** project has potential for further enhancements and expansions, including:

- Integration with other notification channels (SMS, instant messaging platforms).
- Dynamic threshold configuration based on application requirements.
- Detailed reports and analytics on memory usage trends.
- Integration with existing monitoring systems (Nagios, Zabbix, etc.).

## Contributing

Contributions to this project are welcome. To contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes.
4. Push the branch to your forked repository.
5. Open a pull request with a detailed description of your changes.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

We would like to acknowledge the contributions of the open-source community and the valuable resources that helped in the development of this project.

## Contact

For any questions or inquiries, please contact [email protected].
