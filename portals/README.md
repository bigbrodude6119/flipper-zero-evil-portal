# Community Portals

Do you have a great portal that you would like to share? Please submit a pull request placing your portal in this folder. It'd be great to see what the community can come up with! Please also add yourself to this readme so your contribution is recognized.

## Limitations

The ESP32 access point will not have internet access while hosting the portal, as a result there cannot be any requests for stylesheets or javascript such as CDNs for bootstrap and JQuery.

All HTML/CSS/JS must be in a single HTML file. This is due to the fact that the index.html kept in the memory of the esp32.

There is a 20k character limit for each HTML file.

The form data must be sent to the `/get` endpoint as a GET request with the params `email` & `password`. You can put any information you want in these two fields. For example the `email` param can contain a username instead, just keep the param name as `email`.

Please check the example `index.html` to get an idea of what this has to look like. 


## Contributors

Thank you so much to the following contributors for providing awesome portals. 

- `Tech/google_modern.html` by [roshanravan](https://github.com/roshanravan)
- `Social/twitter.html` by [roshanravan](https://github.com/roshanravan)
- `Social/facebook.html` by [roshanravan](https://github.com/roshanravan)
- `ISPs/coxwifi.html` by [qqmajikpp](https://github.com/qqmajikpp)
- `ISPs/starlink.html` by [roshanravan](https://github.com/roshanravan)
- `ISPs/spectrum.html` by [roshanravan](https://github.com/roshanravan)
- `ISPs/t_mobile.html` by [roshanravan](https://github.com/roshanravan)
- `ISPs/verizon.html` by [roshanravan](https://github.com/roshanravan)
- `ISPs/att.html` by [roshanravan](https://github.com/roshanravan)
- `Airlines/southwest_airline.html` by [roshanravan](https://github.com/roshanravan)
- `Airlines/delta_airline.html` by [roshanravan](https://github.com/roshanravan)
- `Airlines/united_airline.html` by [roshanravan](https://github.com/roshanravan)
- `Airlines/american_airline.html` by [roshanravan](https://github.com/roshanravan)
- `Airlines/jet_blue.html` by [roshanravan](https://github.com/roshanravan)
- `Tech/better_google_mobile.html` by [breaching](https://github.com/breaching)
- `Airlines/alaskaairline.html` by [roshanravan](https://github.com/roshanravan)
- `Tech/amazon.html` by [roshanravan](https://github.com/roshanravan)
- `Misc/fakehack.html` by [roshanravan](https://github.com/roshanravan)
- `Misc/matrix.html` by [roshanravan](https://github.com/roshanravan)
- `Tech/microsoft.html` by [roshanravan](https://github.com/roshanravan)
- `Misc/prank_game.html` by [roshanravan](https://github.com/roshanravan)
- `Airlines/spiritairlines.html` by [roshanravan](https://github.com/roshanravan)
- `Social/twitch.html` by [roshanravan](https://github.com/roshanravan)
- `Tech/apple.html` by [Jules](https://github.com/jules0835)
- `Misc/frequency.html` by [roshanravan](https://github.com/roshanravan)

## Disclaimer

Dear User,

Our captive WiFi login portals designed specifically for educational purposes. These portals have been carefully developed to offer a hands-on experience in the field of cybersecurity and penetration testing. As a responsible provider, I would like to emphasize that any illegal use of these portals is strictly prohibited.

It is crucial to acknowledge that using these portals for any unauthorized activities, such as hacking into networks or attempting to access sensitive information without proper authorization, is deemed illegal and unethical. I strongly discourage engaging in any activities that may cause harm, compromise network security, or infringe upon others' privacy rights.

By accessing and utilizing the captive WiFi login portals, users take complete responsibility for their actions and the consequences that may arise from them. I expect users to act responsibly, adhere to ethical guidelines, and ensure that their activities remain within the boundaries of the law and ethical norms.

Remember, these portals are aimed at promoting knowledge, improving cybersecurity skills, and raising awareness about the potential vulnerabilities present in network infrastructures. I encourage you to explore the portals, learn from them, and embrace the opportunity to enhance your understanding in a controlled and legal environment.

Thank you for your cooperation and commitment to responsible usage. Together, let us foster a secure and ethical cyberspace.

Best regards,
[roshanravan](https://github.com/roshanravan)


- `Misc/fakehack2.html` by [roshanravan](https://github.com/roshanravan)
- `ISPs/starlink2.html` by [roshanravan](https://github.com/roshanravan)