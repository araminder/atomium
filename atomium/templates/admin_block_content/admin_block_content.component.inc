<?php

/**
 * @file
 * File admin_block.theme.inc.
 */

/**
 * Implements atomium_theme_alter__hook().
 */
function atomium_theme__admin_block_content() {
  return array(
    'admin_block_content' => array(
      'template' => 'admin-block-content',
      'variables' => array(
        'content' => NULL,
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_admin_block_content().
 */
function atomium_preprocess_admin_block_content(&$variables, $hook) {
  $variables['compact'] = FALSE;

  if (!empty($variables['content'])) {
    $variables['attributes_array']['class'][] = 'admin-list';
    if ($variables['compact'] = system_admin_compact_mode()) {
      $variables['attributes_array']['class'][] = 'compact';
    }
  }

  foreach ($variables['content'] as &$item) {
    $description = '';
    $link = array(
      '#theme' => 'link',
      '#text' => $item['title'],
      '#path' => $item['href'],
      '#options' => $item['localized_options'],
    );
    if (!$variables['compact'] && isset($item['description'])) {
      $description = array(
        '#type' => 'markup',
        '#markup' => filter_xss_admin($item['description']),
      );
    }
    $item = array(
      'link' => $link,
      'description' => $description,
    );
  }
}