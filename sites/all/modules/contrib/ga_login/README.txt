$Id:

This module will allow you to add Google Authenticator support to user logins.

Status
------
A basic proof of concept that is working but isn't integrated in the user login. After you install the module, you'll get to menu's: /ga_login/create to create a new key + QR code and /ga_login/test to test if it's working

Dependencies
------------
  * QR Codes
  * ga4php, you only need the library

Install
-------
Install as usual and copy the ga4php.php file to your module folder.