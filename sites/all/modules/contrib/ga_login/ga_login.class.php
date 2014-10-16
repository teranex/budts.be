<?php
/**
 * @file
 * Our Google Authenticator login class.
 */

include_once 'ga4php.php';

/*
 * Our Google Authenticator login class.
 */
class GALoginGA extends GoogleAuthenticator {

  /**
   * Load data associated with a user.
   */
  public function getData($username) {
    $result = db_select('ga_login')
      ->fields('ga_login', array('keydata'))
      ->condition('name', $username)
      ->execute()
      ->fetchAssoc();

    // Check the result.
    if (!$result) {
      return FALSE;
    }

    // Decrypt the data, if a plugin in available.
    if (module_exists('aes')) {
      return aes_decrypt($result["keydata"]);
    }
    elseif (module_exists('encrypt')) {
      return decrypt($result["keydata"]);
    }

    return $result["keydata"];
  }

  /**
   * Save data associated with a user.
   */
  public function putData($username, $data) {
    // Encrypt the data, if a plugin in available.
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

  /**
   * Not used.
   */
  public function getUsers() {
    // Abstract function from base class.
  }

  /**
   * Create empty data.
   */
  public function createEmptyData() {
    $data = parent::createEmptyData();
    $data["tokentype"] = "TOTP";
    return $data;
  }

  /**
   * Create "user" withOUT insert.
   */
  public function unapprovedUser($username, $ttype = "HOTP", $key = "", $hexkey = "") {
    $ttype = strtoupper($ttype);
    if ($ttype != "HOTP" && $ttype != "TOTP") {
      return FALSE;
    }
    if ($hexkey != "") {
      $hkey = $hexkey;
    }
    else {
      if ($key == "") {
        $key = $this->createBase32Key();
      }
      $hkey = $this->helperb322hex($key);
    }

    $token = $this->internalGetData($username);
    $token["tokenkey"] = $hkey;
    $token["tokentype"] = $ttype;
    return $token;
  }

  /**
   * Create authentication URL.
   */
  public function createURL($user, $data = NULL) {
    if (is_null($data)) {
      return parent::createURL($user);
    }
    else {
      $toktype = $data["tokentype"];
      $key = $this->helperhex2b32($data["tokenkey"]);
      // Token counter should be one more then current token value,
      // otherwise it gets confused.
      $counter = $data["tokencounter"] + 1;
      $toktype = strtolower($toktype);
      if ($toktype == "hotp") {
        $url = "otpauth://$toktype/$user?secret=$key&counter=$counter";
      }
      else {
        $url = "otpauth://$toktype/$user?secret=$key";
      }
      return $url;
    }
  }

  /**
   * Authenticate a user.
   */
  public function authenticateUser($username, $code, $tokendata = FALSE) {
    if (preg_match("/[0-9][0-9][0-9][0-9][0-9][0-9]/", $code) < 1) {
      $this->errorText = "6 digits please";
      return FALSE;
    }
    if ($username && !$tokendata) {
      $tokendata = $this->internalGetData($username);
    }
    if ($tokendata["tokenkey"] == "") {
      $this->errorText = "No Assigned Token";
      return FALSE;
    }

    $ttype = $tokendata["tokentype"];
    $tlid = $tokendata["tokencounter"];
    $tkey = $tokendata["tokenkey"];

    switch ($ttype) {
      case "HOTP":
        $st = $tlid + 1;
        $en = $tlid + $this->hotpSkew;
        for ($i = $st; $i < $en; $i++) {
          $stest = $this->oathHotp($tkey, $i);
          if ($code == $stest) {
            $tokendata["tokencounter"] = $i;
            $this->internalPutData($username, $tokendata);
            return TRUE;
          }
        }
        return FALSE;

      case "TOTP":
        $t_now = REQUEST_TIME;
        $t_ear = $t_now - ($this->totpSkew * $tokendata["tokentimer"]);
        $t_lat = $t_now + ($this->totpSkew * $tokendata["tokentimer"]);
        $t_st = ((int) ($t_ear / $tokendata["tokentimer"]));
        $t_en = ((int) ($t_lat / $tokendata["tokentimer"]));

        // Make sure we only check against newer codes.
        if (isset($tokendata["tokencounter"]) && $tokendata["tokencounter"] >= $t_st) {
          $t_st = $tokendata["tokencounter"] + 1;
        }

        for ($i = $t_st; $i <= $t_en; $i++) {
          $stest = $this->oathHotp($tkey, $i);
          if ($code == $stest) {
            $tokendata["tokencounter"] = $i;
            $this->internalPutData($username, $tokendata);
            return TRUE;
          }
        }
        break;
    }
    return FALSE;
  }
}
