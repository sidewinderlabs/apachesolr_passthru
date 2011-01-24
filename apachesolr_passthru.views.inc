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
  $data['apachesolr_node']['company_name'] = array(
    'title' => t('Company Name'),
    'help' => t('The name of the company.'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
  );
  $data['apachesolr_node']['cro_number'] = array(
    'title' => t('CRO Number'),
    'help' => t('The CRO number of the company.'),
    'field' => array(
      'handler' => 'apachesolr_passthru_handler_field_text',
    ),
    'argument' => array(
      'handler' => 'apachesolr_passthru_handler_argument_text',
    ),
  );
  $data['apachesolr_node']['line_of_business'] = array(
    'title' => t('Line of Business'),
    'help' => t('The company\'s line of business.'),
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
  $data['apachesolr_node']['uk_sic_03'] = array(
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
