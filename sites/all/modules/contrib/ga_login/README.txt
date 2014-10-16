This module will allow you to add Time-based One-time Password Algorithm (also
called "Two Step Authentication" or "Multi-Factor Authentication") support to
user logins. It works with Google's Authenticator app system and support most
(if not all) OATH based HOTP/TOTP systems.

Installation
============

Server-side
-----------
Install and enable the GA Login module.

While optional, it is highly recommended to install either the Mobile Codes or
the QR Codes module:
* Mobile Codes, http://drupal.org/project/mobile_codes
* QR Codes, http://drupal.org/project/qr_codes

By default, the account name used with Google Authenticator for an individual
user is the user's username @ [site name], although this can be configured
at Admin > Configuration > People > GA Login.

Client-side
-----------
Once the server-side installation is finished, each user will have to configure
his or her account for use with Google Authenticator.

Users will need to install the Google Authenticator app or client on their phone
or desktop:
* Google authenticator app for Android, IPhone or Blackberry
  http://www.google.com/support/accounts/bin/answer.py?hl=en&answer=1066447
* Desktop client (should work on all operating systems)
  http://blog.jcuff.net/2011/09/beautiful-two-factor-desktop-client.html
* Windows, Palm OS or Java phone client
  https://code.google.com/p/gauth4win/

To configure an account for use with Google Authenticator, visit the user's
account page, click on the "GA Login"-tab and follow the instructions.
