<?php
/**
 * @file
 * Our Google Authenticator login class.
 */
include_once("ga4php.php");

/*
 * Our Google Authenticator login class.
 */
class ga_loginGA extends GoogleAuthenticator {

  /*
   * Load data associated with a user.
   */
  function getData($username) {
    $result = db_select('ga_login')
      ->fields('ga_login', array('keydata'))
      ->condition('name', $username)
      ->execute()
      ->fetchAssoc();

    // check the result.
    if (!$result) {
      return FALSE;
    }

    // decrypt the data, if a plugin in available
    if (module_exists('aes')) {
      return aes_decrypt($result["keydata"]);
    }
    elseif (module_exists('encrypt')) {
      return decrypt($result["keydata"]);
    }

    return $result["keydata"];
  }

  /*
   * Save data associated with a user.
   */
  function putData($username, $data) {
    // encrypt the data, if a plugin in available
    if (module_exists('aes')) {
      $data = aes_encrypt($data);
    }
    elseif (module_exists('encrypt')) {
      $data = encrypt($data);
    }
    $result = db_merge('ga_login')
      ->key(array('name' => $username))
      ->fields(array('keydata' => $data))
      ->execute();

    if ($result) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /*
   * Not used.
   */
  function getUsers() {
    // abstract function from base class.
  }

  /*
   * Create empty data.
   */
  function createEmptyData() {
    $data = parent::createEmptyData();
    $data["tokentype"] = "TOTP";
    return $data;
  }

  // create "user" withOUT insert
  function unapprovedUser($username, $ttype="HOTP", $key = "", $hexkey="") {
    $ttype = strtoupper($ttype);
    if($ttype != "HOTP" && $ttype !="TOTP") {
      return false;
    }
    if($hexkey != "") {
      $hkey = $hexkey;
    }
    else {
      if($key == "") {
        $key = $this->createBase32Key();
      }
      $hkey = $this->helperb322hex($key);
    }

    $token = $this->internalGetData($username);
    $token["tokenkey"] = $hkey;
    $token["tokentype"] = $ttype;
    return $token;
  }

  function  createURL($user, $data = NULL) {
    if (is_null($data)) {
      return parent::createURL($user);
    }
    else {
      $toktype = $data["tokentype"];
      $key = $this->helperhex2b32($data["tokenkey"]);
      // token counter should be one more then current token value, otherwise
      // it gets confused
      $counter = $data["tokencounter"]+1;
      $toktype = strtolower($toktype);
      if($toktype == "hotp") {
        $url = "otpauth://$toktype/$user?secret=$key&counter=$counter";
      } else {
        $url = "otpauth://$toktype/$user?secret=$key";
      }
      return $url;
    }
  }

}
