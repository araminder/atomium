<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_hook().
 */
function atomium_atomium_theme_links() {
  return array(
    'links' => array(
      'template' => 'links',
      'variables' => array(
        'links' => NULL,
        'attributes' => array(
          'class' => array(
            'links',
          ),
        ),
        'heading' => array(),
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_hook().
 */
function atomium_preprocess_links(&$variables, $hook) {
  global $language_url;

  $heading = $variables['heading'];

  $variables['atomium']['attributes']['wrapper']->merge($variables['attributes']);
  $variables['atomium']['attributes']['wrapper']->append('class', 'links');

  $count = count($variables['links']);
  if ($count > 0) {
    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($variables['heading'])) {
      if (is_string($variables['heading'])) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $variables['heading'] = array(
          'text' => $variables['heading'],
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      if (!empty($variables['heading']['class'])) {
        $variables['atomium']['attributes']['heading']->merge(array(
          'class' => $heading['class'],
        ));
      }
      $variables['heading']['text'] = check_plain($variables['heading']['text']);
    }

    $num_links = $count;
    $i = 1;
    $new_links = array();

    foreach ($variables['links'] as $key => $link) {
      $link['attributes_array'] = array('class' => array($key));
      $link['span_attributes_array'] = array();

      // Add first, last and active classes to the list of links to help out
      // themers.
      if ($i == 1) {
        $link['attributes_array']['class'][] = 'first';
      }
      if ($i == $num_links) {
        $link['attributes_array']['class'][] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
        && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $link['attributes_array']['class'][] = 'active';
      }

      $newlink = '';
      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $newlink = array(
          'link' => array(
            '#theme' => array('link'),
            '#text' => $link['title'],
            '#path' => $link['href'],
            '#options' => $link,
          ),
          '#theme_wrappers' => array('html_tag'),
          '#tag' => 'li',
          '#attributes' => $link['attributes_array'],
        );
      }

      if (isset($link['title']) && !empty($link['title']) && empty($link['href'])) {
        $link['span_attributes_array'] = array();
        if (isset($link['attributes_array'])) {
          $link['span_attributes_array'] = $link['attributes_array'];
        }

        // Some links are actually not links, but we wrap these in <span> for
        // adding title and class attributes.
        if (empty($link['html'])) {
          $newlink = array(
            'link' => array(
              '#markup' => check_plain($link['title']),
              '#theme_wrappers' => array('html_tag'),
              '#tag' => 'span',
              '#attributes' => $link['span_attributes_array'],
            ),
            '#theme_wrappers' => array('html_tag'),
            '#tag' => 'li',
            '#attributes' => $link['attributes_array'],
          );
        }
      }

      $i++;

      $new_links[] = $newlink;
    }

    $variables[$hook] = array(
      $hook => array(
        '#theme' => array('item_list__' . $variables['theme_hook_original']),
        '#items' => $new_links,
        '#type' => 'ul',
        '#atomium' => array(
          'attributes' => array(
            'list' => $variables['atomium']['attributes']['wrapper'],
          ),
        ),
      ),
    );
  }
}
