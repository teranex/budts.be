<?php
/**
 * @file
 * budts_be_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function budts_be_core_taxonomy_default_vocabularies() {
  return array(
    'vocabulary_1' => array(
      'name' => 'side-wide tags',
      'machine_name' => 'vocabulary_1',
      'description' => '',
      'hierarchy' => '1',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
