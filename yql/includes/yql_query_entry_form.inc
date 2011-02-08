<?php
// $Id$

/**
  * yql_query_entry_form page 
  * @file
  * yql_query_entry_form.inc 
  * @package
  * yql.includes
  * The hook required for yql_query_entry_form.
  */

/**
 * Implementation of Form API.
 * Add a form for creating a YQL query
 */

function yql_query_entry_form($form_state) {
  $form = array();

  $form['query'] = array(
    '#type' => 'textfield',
    '#default_value' => 'select * from search.termextract where context="Use Drupal to build everything from personal blogs to enterprise applications"',
    '#size' => 50,
    '#maxlength' => 255,
    '#title' => t('YQL Query Entry'),
    '#collapsible' => TRUE,
    '#description' => t('Use this form to test sending YQL queries'),
  );

  if ($_SESSION['yql_query_results']) {
    $form['query_results'] = array(
      '#type' => 'markup',
      '#title' => 'Query Results',
      '#value' => '<div id="query_results"><p><b>Query Results: </b>' . $_SESSION['yql_query_results'] . '</p></div>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Query'),
  );

  return $form;
}

/**
  * Implementation of Drupal Form API form function.
  * Works similarly to a Drupal hook, in the form of [form_name]_form_validate()
  * In this case we don't need it, but it's here for future purposes
  */
function yql_query_entry_form_validate($form, $form_state) {
  if (empty($form_state['values']['query'])) {
    form_set_error('query', 'You must enter a query');
  }
}

/**
  * Implementation of Drupal Form API form_submit function.
  * Works similarly to a Drupal hook, in the form of [form_name]_form_submit()
  * Also not needed now, but it's here for future purposes
  */
function yql_query_entry_form_submit($form, $form_state) {
  $yql_query_results = yql_query_parse($form_state['values']['query']);
  if ($yql_query_results) {
    if (is_array($yql_query_results)) {
      $_SESSION['yql_query_results'] = implode(',', $yql_query_results);
    }
    else {
      $_SESSION['yql_query_results'] = $yql_query_results;
    }
  }
  else {
    $_SESSION['yql_query_results'] = 'No results';
  }
}
