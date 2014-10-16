<?php

/**
 * @file
 * Abstract GoogleAuthenticator class.
 */

abstract class GoogleAuthenticator {

  /**
   * Constructor.
   */
  public function __construct($totpskew = 1, $hotpskew = 10, $hotphuntvalue = 200000) {
    // The hotpskew is how many tokens forward we look to find the input
    // code the user used.
    $this->hotpSkew = $hotpskew;

    // The totpskew value is how many tokens either side of the current
    // token we should check, based on a time skew.
    $this->totpSkew = $totpskew;

    // The hotphuntvalue is what we use to resync tokens.
    // when a user resyncs, we search from 0 to $hutphutvalue to find
    // the two token codes the user has entered - 200000 seems like overkill
    // really as i cant imagine any token out there would ever make it
    // past 200000 token code requests.
    $this->hotpHuntValue = $hotphuntvalue;
  }

  // Pure abstract functions that need to be overloaded when
  // creating a sub class.
  public abstract function getData($username);
  public abstract function putData($username, $data);
  public abstract function getUsers();

  /**
   * Create an empty data structure, filled with some defaults.
   */
  public function createEmptyData() {
    $data["tokenkey"] = "";
    $data["tokentype"] = "HOTP";
    $data["tokentimer"] = 30;
    $data["tokencounter"] = 1;
    $data["tokenalgorithm"] = "SHA1";
    $data["user"] = "";

    return $data;
  }

  /**
   * Set custom data.
   */
  public function setCustomData($username, $data) {
    $data = $this->internalGetData($username);
    $data["user"] = $key;
    $this->internalPutData($username, $data);
  }

  /**
   * Load custom data.
   */
  public function getCustomData($username) {
    $data = $this->internalGetData($username);
    $custom = $data["user"];
    return $custom;
  }

  /**
   * Load internal data.
   */
  public function internalGetData($username) {
    $data = $this->getData($username);

    $deco = unserialize(base64_decode($data));

    if (!$deco) {
      $deco = $this->createEmptyData();
    }

    return $deco;
  }

  /**
   * Store data.
   */
  public function internalPutData($username, $data) {
    if ($data == "") {
      $enco = "";
    }
    else {
      // $data['user'] = $username;
      $enco = base64_encode(serialize($data));
    }

    return $this->putData($username, $enco);
  }


  /**
   * Sets the token type the user it going to use.
   */
  public function setTokenType($username, $tokentype) {
    $tokentype = strtoupper($tokentype);
    if ($tokentype != "HOTP" && $tokentype != "TOTP") {
      $this->errorText = "Invalid Token Type";
      return FALSE;
    }

    $data = $this->internalGetData($username);
    $data["tokentype"] = $tokentype;
    return $this->internalPutData($username, $data);
  }

  /**
   * Create a user.
   */
  public function setUser($username, $ttype = "HOTP", $key = "", $hexkey = "") {
    $ttype  = strtoupper($ttype);
    if ($ttype != "HOTP" && $ttype != "TOTP") {
      return FALSE;
    }
    if ($key == "") {
      $key = $this->createBase32Key();
    }
    $hkey = $this->helperb322hex($key);
    if ($hexkey != "") {
      $hkey = $hexkey;
    }

    $token = $this->internalGetData($username);
    $token["tokenkey"] = $hkey;
    $token["tokentype"] = $ttype;

    if (!$this->internalPutData($username, $token)) {
      return FALSE;
    }
    return $key;
  }

  /**
   * Determine if the user has an actual token.
   */
  public function hasToken($username) {
    $token = $this->internalGetData($username);
    // @todo change this to a pattern match for an actual key.
    if (!isset($token["tokenkey"])) {
      return FALSE;
    }
    if ($token["tokenkey"] == "") {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Sets a users key.
   */
  public function setUserKey($username, $key) {
    $token = $this->internalGetData($username);
    $token["tokenkey"] = $key;
    $this->internalPutData($username, $token);

    // @todo error checking.
    return TRUE;
  }

  /**
   * Delete a user.
   */
  public function deleteUser($username) {
    $this->internalPutData($username, "");
  }

  /**
   * Authenticate a user using a code.
   */
  public function authenticateUser($username, $code) {
    if (preg_match("/[0-9][0-9][0-9][0-9][0-9][0-9]/", $code) < 1) {
      $this->errorText = "6 digits please";
      return FALSE;
    }

    $tokendata = $this->internalGetData($username);
    if ($tokendata["tokenkey"] == "") {
      $this->errorText = "No Assigned Token";
      return FALSE;
    }
    // @todo check return value.
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
        $t_now = time();
        $t_ear = $t_now - ($this->totpSkew * $tokendata["tokentimer"]);
        $t_lat = $t_now + ($this->totpSkew * $tokendata["tokentimer"]);
        $t_st = ((int) ($t_ear / $tokendata["tokentimer"]));
        $t_en = ((int) ($t_lat / $tokendata["tokentimer"]));
        for ($i = $t_st; $i <= $t_en; $i++) {
          $stest = $this->oathHotp($tkey, $i);
          error_log("testing code: $code, $stest, $tkey\n");
          if ($code == $stest) {
            return TRUE;
          }
        }
        break;

      default:
        return FALSE;
    }

    return FALSE;
  }

  /**
   * Resync codes.
   */
  public function resyncCode($username, $code1, $code2) {
    $tokendata = $this->internalGetData($username);

    // @todo check return value.
    $ttype = $tokendata["tokentype"];
    $tlid = $tokendata["tokencounter"];
    $tkey = $tokendata["tokenkey"];

    if ($tkey == "") {
      $this->errorText = "No Assigned Token";
      return FALSE;
    }

    switch ($ttype) {
      case "HOTP":
        $st = 0;
        $en = $this->hotpHuntValue;
        for ($i = $st; $i < $en; $i++) {
          $stest = $this->oathHotp($tkey, $i);
          if ($code1 == $stest) {
            $stest2 = $this->oathHotp($tkey, $i + 1);
            if ($code2 == $stest2) {
              $tokendata["tokencounter"] = $i + 1;
              $this->internalPutData($username, $tokendata);
              return TRUE;
            }
          }
        }
        return FALSE;

      case "TOTP":
        break;

      default:
        echo "how the frig did i end up here?";
    }

    return FALSE;
  }

  /**
   * Gets the error text associated with the last error.
   */
  public function getErrorText() {
    return $this->errorText;
  }

  /**
   * Create a url compatibile with google authenticator.
   */
  public function createURL($user) {
    // HOTP needs to be lowercase.
    $data = $this->internalGetData($user);
    $toktype = $data["tokentype"];
    $key = $this->helperhex2b32($data["tokenkey"]);
    // Token counter should be one more then current token value.
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

  /**
   * Creates a base 32 key (random).
   */
  public function createBase32Key() {
    $alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    $key = "";
    for ($i = 0; $i < 16; $i++) {
      $offset = rand(0, strlen($alphabet) - 1);
      $key .= $alphabet[$offset];
    }

    return $key;
  }

  /**
   * Get hex key.
   */
  public function getKey($username) {
    $data = $this->internalGetData($username);
    $key = $data["tokenkey"];

    return $key;
  }

  /**
   * Get token type.
   */
  public function getTokenType($username) {
    $data = $this->internalGetData($username);
    $toktype = $data["tokentype"];

    return $toktype;
  }

  /**
   * Convert b32 to hex.
   */
  public function helperb322hex($b32) {
    $alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    $out = "";
    $dous = "";

    for ($i = 0; $i < strlen($b32); $i++) {
      $in = strrpos($alphabet, $b32[$i]);
      $b = str_pad(base_convert($in, 10, 2), 5, "0", STR_PAD_LEFT);
      $out .= $b;
      $dous .= $b . ".";
    }

    $ar = str_split($out, 20);

    $out2 = "";
    foreach ($ar as $val) {
      $rv = str_pad(base_convert($val, 2, 16), 5, "0", STR_PAD_LEFT);
      $out2 .= $rv;
    }
    return $out2;
  }

  /**
   * Convert hax to b32.
   */
  public function helperhex2b32($hex) {
    $alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    $ar = str_split($hex, 5);

    $out = "";
    foreach ($ar as $var) {
      $bc = base_convert($var, 16, 2);
      $bin = str_pad($bc, 20, "0", STR_PAD_LEFT);
      $out .= $bin;
    }

    $out2 = "";
    $ar2 = str_split($out, 5);
    foreach ($ar2 as $var2) {
      $bc = base_convert($var2, 2, 10);
      $out2 .= $alphabet[$bc];
    }

    return $out2;
  }

  /**
   * Create HOTP.
   */
  public function oathHotp($key, $counter) {
    $key = pack("H*", $key);
    $cur_counter = array(0, 0, 0, 0, 0, 0, 0, 0);
    for ($i = 7; $i >= 0; $i--) {
      $cur_counter[$i] = pack('C*', $counter);
      $counter = $counter >> 8;
    }
    $bin_counter = implode($cur_counter);

    // Pad to 8 chars.
    if (strlen($bin_counter) < 8) {
      $bin_counter = str_repeat(chr(0), 8 - strlen($bin_counter)) . $bin_counter;
    }

    // HMAC.
    $hash = hash_hmac('sha1', $bin_counter, $key);
    return str_pad($this->oathTruncate($hash), 6, "0", STR_PAD_LEFT);
  }

  /**
   * Truncate.
   */
  public function oathTruncate($hash, $length = 6) {
    // Convert to dec,
    foreach (str_split($hash, 2) as $hex) {
      $hmac_result[] = hexdec($hex);
    }

    // Find offset.
    $offset = $hmac_result[19] & 0xf;

    // Algorithm from RFC.
    return
      (
        (($hmac_result[$offset + 0] & 0x7f) << 24) |
        (($hmac_result[$offset + 1] & 0xff) << 16) |
        (($hmac_result[$offset + 2] & 0xff) << 8) |
        ($hmac_result[$offset + 3] & 0xff)
      ) % pow(10, $length);
  }

  // Some private data bits.
  private $getDatafunction;
  private $putDatafunction;
  private $errorText;
  private $errorCode;

  protected $hotpSkew;
  protected $totpSkew;

  protected $hotpHuntValue;

  /*
   * error codes
   * 1: Auth Failed
   * 2: No Key
   * 3: input code was invalid (must be 6 numerical digits)
   * 4: user doesnt exist?
   * 5: key invalid
   */
}
