<?php

/**
 * @file
 * ga_login pages.
 */

/**
 * Form to create a new code.
 *
 * @see _ga_login_explanation_form()
 * @see _ga_login_create_form()
 * @see _ga_login_code_approve_form()
 */
function ga_login_create_form($form, &$form_state, $account) {
  if (empty($form_state['step'])) {
    $form_state['step'] = 0;
  }
  $step = $form_state['step'];

  switch ($step) {
    case 0:
      return _ga_login_explanation_form($form, $form_state, $account);

    case 1:
      return _ga_login_create_form($form, $form_state, $account);

    case 2:
      return _ga_login_code_approve_form($form, $form_state, $account);
  }
}

/**
 * Form to create a new code - Introduction.
 */
function _ga_login_explanation_form($form, &$form_state, $account) {
  $form['two_step_verification'] = array(
    '#type' => 'container',
    '#title' => t('Two step verification'),
    '#prefix' => '<h2>' . t('Two step verification') . '</h2>',
  );
  $form['two_step_verification']['security'] = array(
    '#markup' => '<h3>' . t('2-step verification adds an extra layer of security to your account') . '</h3>' .
    t("In addition to your username and password, you'll enter a code that Google will send you via their !mobile_app.
      If you do not have a smartphone, you can use the !desktop_client (should work on all operating systems) or a !phone_client.",
      array(
        '!mobile_app' => l(t('mobile app'), 'http://support.google.com/accounts/bin/answer.py?hl=en&answer=1066447', array('attributes' => array('target' => '_blank'))),
        '!desktop_client' => l(t('desktop client'), 'http://blog.jcuff.net/2011/09/beautiful-two-factor-desktop-client.html', array('attributes' => array('target' => '_blank'))),
        '!phone_client' => l(t('windows/palm os/java phone client'), 'http://code.google.com/p/gauth4win/', array('attributes' => array('target' => '_blank'))),
      )
    ),
  );
  $howitworks1 = array(
    '#type' => 'item',
    '#title' => t('Enter your password'),
    '#markup' => t("Whenever you sign in you'll enter your username and password as usual."),
  );
  $howitworks2 = array(
    '#type' => 'item',
    '#title' => t('Enter a code from your phone'),
    '#markup' => t("Then, you'll be asked for a code that will be sent to you via your mobile app."),
  );
  $suffix = t('To get this code you have to add the data you will see after completing this form, using you mobile app.');
  if (module_exists('mobile_codes')) {
    $suffix = t('To get this code you have to scan the bar code or manually add the data you will see after completing this form, using your mobile app.');
  }
  $form['two_step_verification']['how_it_works'] = array(
    '#theme' => 'item_list',
    '#type' => 'ol',
    '#title' => t('How it works'),
    '#items' => array(
      drupal_render($howitworks1),
      drupal_render($howitworks2),
    ),
    '#suffix' => $suffix,
  );

  $types = variable_get('ga_login_generation_types', 'BOTH');
  $hotptotp1 = array(
    '#type' => 'item',
    '#title' => t('Time-based code'),
    '#markup' => t('A time-based code will refresh (generate a new code) every time a certain amount of time has passed. It is considered to be more secure than a counter-based code.'),
  );
  $hotptotp2 = array(
    '#type' => 'item',
    '#title' => t('Counter-based code'),
    '#markup' => t('A counter-based code will only refresh if you do so manually in the mobile app.'),
  );
  $form['hotptotp'] = array(
    '#theme' => 'item_list',
    '#title' => format_plural(($types == 'BOTH' ? 2 : 1), 'Supported code', 'Supported codes'),
    '#items' => array(),
  );
  switch ($types) {
    case 'TOTP':
      $form['hotptotp']['#items'] = array(
        drupal_render($hotptotp1),
      );
      break;

    case 'HOTP':
      $form['hotptotp']['#items'] = array(
        drupal_render($hotptotp2),
      );
      break;

    default:
      $form['hotptotp']['#items'] = array(
        drupal_render($hotptotp1),
        drupal_render($hotptotp2),
      );
      break;
  }

  // Keep track of uid, so we can skip a step if needed.
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Get started'),
  );
  return $form;
}

/**
 * Form to create a new code - step 1.
 */
function _ga_login_create_form($form, &$form_state, $account) {
  $form['info'] = array(
    '#type' => 'item',
    '#markup' => t('Everytime you submit this form a new key will be generated and you will have to re-enter the data in your mobile app.'),
    '#weight' => -1,
  );
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );
  $form['tokentype'] = array(
    '#title' => t('Code type'),
    '#type' => 'select',
    '#options' => array(
      'TOTP' => t('Time-based code'),
      'HOTP' => t('Counter-based code'),
    ),
    '#default_value' => 'TOTP',
    '#required' => TRUE,
    '#description' => t('Select the type of code you want to create.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create code'),
  );
  return $form;
}

/**
 * Form to create a new code - step 2.
 */
function _ga_login_code_approve_form($form, &$form_state, $account) {
  $url = $form_state['url'];
  $data = $form_state['data'];

  $form['warning'] = array(
    '#type' => 'item',
    '#markup' => t("This login code will only be activated on this site once you've submitted this form. As long as you don't submit this form, you will not be able to log in on this site using this code."),
    '#title' => t('Warning!'),
  );

  $form['type'] = array(
    '#type' => 'item',
    '#markup' => $data['tokentype'] == 'TOTP' ? t('Time-based') : t('Counter-based'),
    '#title' => t('Type'),
  );

  $form['url'] = array(
    '#type' => 'item',
    '#markup' => $url,
    '#title' => t('URL'),
  );

  $form['account'] = array(
    '#type' => 'item',
    '#markup' => $data['username'],
    '#title' => t('Account'),
  );

  $form['key'] = array(
    '#type' => 'item',
    '#markup' => '<span class="secret-key">' . $data['secret'] . '</span>',
    '#title' => t('Key'),
  );

  // Generate barcode.
  $img = $file = '';
  if (module_exists('mobile_codes')) {
    $variables = array(
      'data' => $url,
      'attributes' => array(
        '#preset' => 'ga_login',
      ),
    );
    $path = mobile_codes_process_url($variables['data'], $variables['attributes']);
    $file = 'public://mobile_codes/' . md5(serialize($path)) . '.png';
    $img = theme('mobilecode', $variables);
  }

  if (!empty($img)) {
    $form['current'] = array(
      '#type' => 'item',
      '#title' => t('Barcode'),
      '#markup' => $img,
    );
  }

  $form['code_image_path'] = array(
    '#type' => 'value',
    '#value' => $file,
  );
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );
  $form['verify_code'] = array(
    '#type' => 'gacode',
    '#uid' => $account->uid,
    '#title' => t('Code'),
    '#description' => t('Please enter the code that appears on your authenticator device.'),
    '#required' => TRUE,
    // Set a flag for the #element_validate callback not to check the db, as
    // this is a new code.
    '#_new_ga_code' => TRUE,
  );
  $form['approve_current_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Use this code'),
  );
  return $form;
}

/**
 * Validation handler to create a new code.
 */
function ga_login_create_form_validate($form, &$form_state) {
  if ($form_state['step'] == '2' && !form_get_errors()) {
    $uid = $form_state['values']['uid'];
    $account = user_load($uid);
    $username = _ga_login_username($account);
    $ga = _ga_login_get_class();
    $correct = $ga->authenticateUser($username, $form_state['values']['verify_code'], $form_state['data']);
    if (!$correct) {
      form_set_error('verify_code', 'The code you entered was not valid, you must enter the code generated by your authenticator to continue');
    }
  }
}

/**
 * Submit handler to create a new code.
 */
function ga_login_create_form_submit($form, &$form_state) {
  // If admin only allows one generation type, then assign that type
  // and skip the first page.
  $types = variable_get('ga_login_generation_types', 'BOTH');
  if ($form_state['step'] == '0' && $types != 'BOTH') {
    $form_state['values']['tokentype'] = $types;
    $form_state['step']++;
  }

  $step = $form_state['step'];
  switch ($step) {
    case '1':
      $account = user_load($form_state['values']['uid']);
      $username = _ga_login_username($account);
      $ga = _ga_login_get_class();
      // don't save the data to the db until the user approves it.
      $data = $ga->unapprovedUser($username, $form_state['values']['tokentype']);
      $data['secret'] = $ga->helperhex2b32($data['tokenkey']);
      $form_state['url'] = $ga->createURL($username, $data);
      $data['username'] = _ga_login_username($account, FALSE);
      $form_state['data'] = $data;
      break;

    case '2':
      if (isset($form_state['values']['approve_current_submit'])) {
        // Don't need to save the code here, since the
        // ga_login_create_form_validate function does that for us.
        $account = user_load($form_state['values']['uid']);

        // Enable TFA for this account after they generate a code.
        user_save($account, array('data' => array('ga_login_force_tfa' => TRUE)));

        if (module_exists('mobile_codes')) {
          if (file_unmanaged_delete($form_state['values']['code_image_path'])) {
            drupal_set_message(t('Mobile code image was successfully deleted.'));
          }
          else {
            drupal_set_message(t('Error while trying to delete the mobile code image.'), 'error');
          }
        }

        // Redirect the user to the page specified by the adminsitrator.
        $destination = variable_get('ga_login_redirect_after_save', '');
        switch ($destination) {
          case '':
            // Only redirect if user has still access.
            if (user_access('create own login code', $account) || user_access('create others login codes', $account)) {
              $form_state['redirect'] = 'user/' . $account->uid . '/ga_login';
            }
            else {
              $form_state['redirect'] = 'user/' . $account->uid;
            }
            break;

          case '<front>':
            $form_state['redirect'] = '';
            break;

          default:
            $form_state['redirect'] = $destination;
            break;
        }
      }
      drupal_set_message(t('You can now log in with your new code.'));
      break;
  }
  $form_state['step']++;
  if ($form_state['step'] > 2) {
    $form_state['step'] = 0;
  }

  if ($step == '0' || $step == '1') {
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * The confirmation page for deleting a GA Login code.
 */
function ga_login_delete_form($form, &$form_state, $account) {
  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );
  return confirm_form($form,
    t('Delete the GA Login code for @name?', array('@name' => format_username($account))),
    'user/' . $account->uid . '/edit',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * The submit handler for deletign a GA Login code.
 */
function ga_login_delete_form_submit($form, &$form_state) {
  $account = $form_state['values']['account'];
  ga_login_delete_code($account);
  drupal_goto('user/' . $account->uid . '/edit');
}
