<?php

/**
 * @file
 * Defines a Google Search Collections preset add/edit form.
 */

$plugin = array(
  'schema' => 'google_search_collections',
  'access' => 'administer google search collections',
  'menu' => array(
    'menu item' => 'google-search-collections',
    'menu title' => 'Google search collections',
    'menu description' => 'Administer google search collections.',
  ),
  'title singular' => t('collection'),
  'title plural' => t('collections'),
  'title singular proper' => t('Google search collection'),
  'title plural proper' => t('Google search collections'),
  'form' => array(
    'settings' => 'google_search_collections_ctools_export_ui_form',
  ),
);


/**
 * Define the search collection add/edit form.
 */
function google_search_collections_ctools_export_ui_form(&$form, &$form_state) {
  $preset = $form_state['item'];

  // Create a vertical tab set.
  $form['tabs'] = array('#type' => 'vertical_tabs');

  // Modify the "info" key to be a fieldset.
  $form['info']['#title'] = t('Collection details');
  $form['info']['#type'] = 'fieldset';
  $form['info']['#group'] = 'tabs';

  // Provide a fieldset to contain all "data" customization attributes.
  $form['data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Customizations'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'tabs',
    '#tree' => TRUE,
  );

  // Provide more useful description text for the path field.
  $form['info']['path']['#description'] = t('The unique URL path part for this collection. Once saved, this cannot be changed.');

  // Search collection title.
  $form['info']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Collection title'),
    '#description' => t('The title for this search collection, displayed to end-users.'),
    '#default_value' => $preset->title,
    '#required' => TRUE,
  );

  // Search collection description.
  $form['info']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('Enter notes about this search collection for yourself or future administrators.'),
    '#default_value' => $preset->description,
  );

  // Module.
  $form['data']['module'] = array(
    '#type' => 'select',
    '#title' => t('Module'),
    '#description' => t('The module that powers this search collection.'),
    '#default_value' => isset($preset->data['module']) ? $preset->data['module'] : '',
    '#options' => array(),
    '#required' => TRUE,
  );

  if (module_exists('gss')) {
    $form['data']['module']['#options']['gss'] = t('Google Site Search');
  }
  if (module_exists('google_appliance')) {
    $form['data']['module']['#options']['google_appliance'] = t('Google Search Appliance');
  }

  // Query terms.
  $form['data']['queryterms'] = array(
    '#type' => 'textfield',
    '#title' => t('Query terms'),
    '#description' => t('Special query terms that are appended to all searches performed within this collection.'),
    '#default_value' => isset($preset->data['queryterms']) ? $preset->data['queryterms'] : '',
  );

  // Collection weight.
  $form['data']['weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#description' => t('Determines the display order of this collection relative to others.'),
    '#default_value' => isset($preset->data['weight']) ? $preset->data['weight'] : 0,
    '#options' => drupal_map_assoc(array(-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)),
  );
}
