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
  $data['apachesolr_node']['address_line_1'] = array(
    'title' => t('Address Line 1'),
    'help' => t('The company\'s address (line 1).'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['address_line_2'] = array(
    'title' => t('Address Line 2'),
    'help' => t('The company\'s address (line 2).'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['address_line_3'] = array(
    'title' => t('Address Line 3'),
    'help' => t('The company\'s address (line 3).'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['address_line_4'] = array(
    'title' => t('Address Line 4'),
    'help' => t('The company\'s address (line 4).'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['company_number'] = array(
    'title' => t('Company Number'),
    'help' => t('The Company\'s House number of the company.'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
    'argument' => array(
      'handler' => 'apachesolr_passthru_handler_argument_text',
    ),
  );
  $data['apachesolr_node']['name'] = array(
    'title' => t('Company Name'),
    'help' => t('The name of the company.'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['postcode'] = array(
    'title' => t('Postcode'),
    'help' => t('The company\'s postcode.'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['sic_trade_classification_code'] = array(
    'title' => t('SIC(03)'),
    'help' => t('The company\'s SIC(03) code.'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
    'filter' => array(
      'handler' => 'apachesolr_passthru_handler_filter_text',
    ),
  );
}
