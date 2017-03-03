<?php

/**
 * @file
 * Feed_icon.theme.inc.
 */

/**
 * Implements atomium_theme_alter__hook().
 */
function atomium_theme__feed_icon() {
  return array(
    'feed_icon' => array(
      'template' => 'feed-icon',
      'variables' => array(
        'url' => NULL,
        'title' => NULL,
        'link' => NULL,
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_feed_icon().
 */
function atomium_preprocess_feed_icon(&$variables) {
  $variables['link'] = '';

  $text = t('Subscribe to !feed-title', array('!feed-title' => $variables['title']));
  if ($image = theme('image', array(
    'path' => 'misc/feed.png',
    'width' => 16,
    'height' => 16,
    'alt' => $text,
  ))) {
    $variables['link'] = array(
      '#theme' => 'link',
      '#text' => $image,
      '#path' => $variables['url'],
      '#options' => array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('feed-icon'),
          'title' => $text,
        ),
      ),
    );
  }
}