<?php

/**
 * @file
 * Theme function for ga_login module.
 */

/**
 * Returns HTML for the gacode field.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #placeholder,
 *     #required, #attributes.
 *
 * @ingroup themeable
 */
function theme_gacode($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'number';

  // Hard-coded values.
  $element['#min'] = 0;
  $element['#max'] = 999999;
  $element['#step'] = 1;
  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'step',
    'min',
    'max',
    'step',
    'placeholder',
  ));
  _form_set_class($element, array('form-text', 'form-galogin'));

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output;
}
