<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_hook().
 */
function atomium_atomium_theme_filter_guidelines() {
  return array(
    'filter_guidelines' => array(
      'template' => 'filter-guidelines',
      'variables' => array(
        'format' => NULL,
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_hook().
 */
function atomium_preprocess_filter_guidelines(&$variables, $hook) {
  $variables['name'] = check_plain($variables['format']->name);
  $variables['tips'] = array(
    '#theme' => 'filter_tips',
    '#tips' => _filter_tips($variables['format']->format, FALSE),
  );
}
