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
    '#type' => 'textfield',
    '#title' => t('TOTP skew'),
    '#description' => t('The TOTP skew value is how many tokens either side of the current token we should check.'),
    '#default_value' => variable_get('ga_login_totp_skew', 10),
    '#element_validate' => array('ga_login_validate_skew'),
    '#size' => 10,
  );

  $form['ga_login_hotp_skew'] = array(
    '#type' => 'textfield',
    '#title' => t('HOTP skew'),
    '#description' => t('The HOTP skew is how many tokens forward we look to find the input code the user used.'),
    '#default_value' => variable_get('ga_login_hotp_skew', 10),
    '#element_validate' => array('ga_login_validate_skew'),
    '#size' => 10,
  );

  return system_settings_form($form);
}

function ga_login_validate_skew($element, $form, &$form_state) {
  if (!ctype_digit($element['#value'])) {
    form_error($element, t('@title must be a positive integer.', array('@title' => $element['#title'])));
  }
}
