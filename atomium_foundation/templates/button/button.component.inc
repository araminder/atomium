<?php

/**
 * @file
 * Button.preprocess.inc.
 */

/**
 * Implements hook_preprocess_button().
 */
function atomium_foundation_preprocess_button(&$variables) {
  $variables['attributes_array']['class'][] = 'button';
}