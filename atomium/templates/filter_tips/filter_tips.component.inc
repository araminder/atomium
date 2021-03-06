<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_hook().
 */
function atomium_atomium_theme_filter_tips() {
  return array(
    'filter_tips' => array(
      'template' => 'filter-tips',
      'variables' => array(
        'tips' => NULL,
        'long' => FALSE,
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_hook().
 */
function atomium_preprocess_filter_tips(&$variables, $hook) {
  $items = array();

  foreach ($variables['tips'] as $name => $tip_list) {
    foreach ($tip_list as $key => $tip) {
      $items[$key] = array(
        '#theme' => array('html_tag__' . $variables['theme_hook_original']),
        '#tag' => 'li',
        '#atomium' => array(
          'attributes' => array(
            'element' => array(
              'class' => array($name),
              'id' => $tip['id'],
            ),
          ),
        ),
        '#value' => $tip['tip'],
      );
    }
  }

  $variables[$hook] = array(
    $hook => array(
      '#theme' => array('item_list__' . $variables['theme_hook_original']),
      '#items' => $items,
      '#theme_wrapper' => array(
        'container',
      ),
    ),
  );
}
