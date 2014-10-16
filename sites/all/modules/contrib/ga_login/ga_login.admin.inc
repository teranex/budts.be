<?php

/**
 * @file
 * Administrative forms for ga_login.
 */

/**
 * Admin settings form callback.
 */
function ga_login_admin_settings_form($form, $form_state) {
  $form['ga_login_always_for_uid1'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force uid 1 to use ga login'),
    '#description' => t("If you want force uid 1 to use ga login, you'll have to enable this option."),
    '#default_value' => variable_get('ga_login_always_for_uid1', 0),
  );

  $form['ga_login_textname'] = array(
    '#type' => 'textfield',
    '#title' => t('Realm'),
    '#description' => t('The realm is combined with the Drupal username to form the GA Login accountname.'),
    '#default_value' => variable_get('ga_login_textname', variable_get('site_name', 'Drupal')),
    '#required' => TRUE,
    '#size' => 10,
  );

  $form['ga_login_textid'] = array(
    '#type' => 'textfield',
    '#title' => t('Account suffix'),
    '#description' => t("Text to append to all login URL's. This is handy if you want to differentiate between development and production versions."),
    '#default_value' => variable_get('ga_login_textid', ''),
    '#size' => 10,
  );

  $form['ga_login_warning'] = array(
    '#markup' => t('<strong>WARNING:</strong> Changing the realm or account suffix will cause all previously configured GA accounts to become invalid, and users will need to re-configure 2-factor authentication for their account.'),
  );

  $form['ga_login_totp_skew'] = array(
    '#type' => module_exists('elements') ? 'numberfield' : 'textfield',
    '#title' => t('TOTP skew'),
    '#description' => t('The TOTP skew value is how many tokens either side of the current token we should check.'),
    '#default_value' => variable_get('ga_login_totp_skew', 10),
    '#element_validate' => array('element_validate_integer_positive'),
    '#size' => 10,
  );

  $form['ga_login_hotp_skew'] = array(
    '#type' => module_exists('elements') ? 'numberfield' : 'textfield',
    '#title' => t('HOTP skew'),
    '#description' => t('The HOTP skew is how many tokens forward we look to find the input code the user used.'),
    '#default_value' => variable_get('ga_login_hotp_skew', 10),
    '#element_validate' => array('element_validate_integer_positive'),
    '#size' => 10,
  );

  $form['ga_login_redirect_after_save'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect after saving a new ga login code.'),
    '#description' => t('Leaving blank will return the user back to page one of the form (default behaviour), &#60;front&#62; will send them to the front page.'),
    '#default_value' => variable_get('ga_login_redirect_after_save', ''),
    '#size' => 30,
  );

  $form['ga_login_generation_types'] = array(
    '#type' => 'select',
    '#title' => t('Enable key generation types.'),
    '#description' => t('Force users to use a specific key generation type.'),
    '#options' => array(
      'BOTH' => 'Both time and counter based',
      'TOTP' => 'Time-based only',
      'HOTP' => 'Counter-based only',
    ),
    '#default_value' => variable_get('ga_login_generation_types', 'BOTH'),
  );

  return system_settings_form($form);
}
