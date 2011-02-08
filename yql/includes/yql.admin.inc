<?php 
// $Id$
/**
 * @file
 * Create administrative settings
 */

/**
 * Implementation hook_menu().
 * Gives admin section for yql
 */

function yql_menu() {
  $items['admin/settings/yql'] = array(
    'title' => 'YQL API settings',
    'description' => 'Settings for the YQL API Module',
    'position' => 'right',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('yql_admin_settings'),
    'access callback' => 'user_access',
    'access arguments' => array('administer yql')
  );

  return $items;
}

/**
 * Implementation of hook_perm().
 */
function yql_perm() {
  return array('administer yql', 'use yql queries');
}

/** 
 * Implementation hook_settings().
 * Allows users to enter in settings for the yql module
 */

function yql_admin_settings() {
  $form['yql_url'] = array(
    '#type' => 'textfield',
    '#title' => t('YQL URL'),
    '#description' => t('The Yahoo URL to pass YQL to'),
    '#default_value' => variable_get('yql_url', 'http://query.yahooapis.com/v1/public/yql?q='),
  );
  $form['yql_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('YQL Debugging Mode'),
    '#description' => t('Check this box to enable YQL Debuggin Mode. Will return errors. You should probably also set your site error handling settings to show errors on screen'),
    '#default_value' => variable_get('yql_debug', '0'),
  );
  return system_settings_form($form);
}
