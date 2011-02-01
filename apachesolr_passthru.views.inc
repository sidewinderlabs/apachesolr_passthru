<?php
// $Id$
/**
* Implementation of hook_views_handlers().
*/
function apachesolr_passthru_views_handlers() {
  return array(
    'info' => array(
      'modulename' => 'apachesolr_views',
      'path' => drupal_get_path('module', 'apachesolr_passthru') .'/handlers',
    ),
    'handlers' => array(
      'apachesolr_passthru_handler_argument_text' => array(
        'parent' => 'views_handler_argument',
      ),
      'apachesolr_passthru_handler_field_text' => array(
        'parent' => 'views_handler_field',
      ),
      'apachesolr_passthru_handler_filter_text' => array(
        'parent' => 'views_handler_filter_string',
      ),
    ),
  );
}

/**
* Implementation of hook_views_data_alter(&$data).
*/
function apachesolr_passthru_views_data_alter(&$data) {
  $fields = _get_apachesolr_passthru_field_list();

  foreach($fields as $field) {
	$data['apachesolr_node'][$field[0]] = array(
	  'title' => t($field[0]),
	  'help' => t("Pass-thru index:" . $field[0]),
      'argument' => array(
        'handler' => 'apachesolr_passthru_handler_argument_text',
      ),
	  'field' => array(
	    'handler' => 'apachesolr_passthru_handler_field_text',
	  ),
      'filter' => array(
        'handler' => 'apachesolr_passthru_handler_filter_text',
      ),
	);
  }
}
