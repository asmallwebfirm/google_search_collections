<?php

/**
 * @file
 * Contains admin hooks and callbacks for the Google Search Collections module.
 */


/**
 * Page callback for global admin settings.
 */
function google_search_collections_settings($form) {
  // The default search collection.
  $options = _google_search_collections_get_collection_options();
  $fallback = google_search_collections_get_default_collection();
  $form['google_search_collections_default_collection'] = array(
    '#type' => 'select',
    '#title' => t('Default collection'),
    '#description' => t('Controls which collection is used as the default (e.g. when searches are performed from the block form).'),
    '#required' => TRUE,
    '#default_value' => variable_get('google_search_collections_default_collection', $fallback),
    '#options' => $options,
  );

  return system_settings_form($form);
}

function _google_search_collections_get_collection_options() {
  $options = array();
  foreach (google_search_collections_get_definitions() as $path => $def) {
    $options[$path] = $def->title;
  }
  return $options;
}
