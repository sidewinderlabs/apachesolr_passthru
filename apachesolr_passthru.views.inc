<?php
// $Id$
/**
 * Implementation of hook_views_handlers().
 */

function apachesolr_passthru_views_data() {
  $view = NULL;
  $display_name = NULL;

  $solr_servers = apachesolr_passthru_get_servers() ;
  
  foreach($solr_servers as $solr_server) {
    $table_name = 'solr_server_' . $solr_server['name'];
    
    // TODO: save human name as well
    $data[$table_name]['table']['group'] = 'Solr Server';
    $data[$table_name]['table']['base'] = array(
      'title' => t('Solr Query ' . $solr_server['name']),
      'help' => t('Solr search independent of Drupal schema.'),
      'query class' => 'apachesolr_passthru_views_query',
    ); 

    
    // The solr search should have a search term
    $data[$table_name]['text'] = array(
      'title' => t('Search'),
      'help' => t('Searches the content with Solr'),
      'filter' => array(
        'handler' => 'apachesolr_views_handler_filter_search',
      ),
      'argument' => array(     
        'handler' => 'apachesolr_views_handler_argument_search',     
      ),
    );

    $fields = _get_apachesolr_passthru_field_list($solr_server['solr_url'],$solr_server['solr_port'],$solr_server['solr_path']);
    foreach($fields as $field) {
      $data[$table_name][$field[0]] = array(
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
  
  krumo($data);

  return $data;
}

function apachesolr_passthru_views_handlers() {
  $path = drupal_get_path('module', 'apachesolr_passthru') . '/handlers';
  return array(
    'info' => array(
      'modulename' => 'apachesolr_views',
      'path' => $path,
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

/* implements hook_views_plugins */
function apachesolr_passthru_views_plugins() {
  $path = drupal_get_path('module', 'apachesolr_passthru') . '/handlers';
  return array(
   'module' => 'apachesolr_passthru',  
   'query' => array(
      'apachesolr_passthru_views_query' => array(
        'title' => t('Apache Passthru Solr Query'), 
        'help' => t('Query that allows you to search any solr server.'),
        'handler' => 'apachesolr_passthru_views_query',
        'parent' => 'apachesolr_views_query',
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
