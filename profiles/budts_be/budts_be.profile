<?php

// dummy installation profile

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 */
function budts_be_profile_details() {
  return array(
    'name' => 'Budts.be',
    'description' => 'Dummy installation profile for budts.be'
  );
}

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return
 *   An array of modules to enable.
 */
function budts_be_profile_modules() {
  return array();
}
