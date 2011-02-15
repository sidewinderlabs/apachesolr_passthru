<?php



/**
 * Class for handling a view that gets its data not from the database, but from
 * a Solr server.
 */
class apachesolr_passthru_views_query extends apachesolr_views_query implements Drupal_Solr_Query_Interface {
  
  public function init($base_table, $base_field, $options) {
    $this->base_table = $base_table;
    $this->base_field = $base_field;
    $this->sql_base_table = substr($base_table, 11);
    
    // Determine the solr server name from the base table name
    // TODO: Investigate if this can be passed as an option.
    $solr_server_name = str_replace('solr_server_','',$base_table);
    $solr_server_details = apachesolr_passthru_get_server($solr_server_name);
    
    $this->solr_host = $solr_server_details['solr_host'];
    $this->solr_port = $solr_server_details['solr_port'];
    $this->solr_path = $solr_server_details['solr_path'];
    
    $this->_solr_service = apachesolr_get_solr($this->solr_host,$this->solr_port,$this->solr_path);

    
    
    module_load_include('inc', 'views', 'plugins/views_plugin_query_default');
    $this->_db_query = new views_plugin_query_default;
    $this->_db_query->init($this->sql_base_table, $base_field, $options);

    $this->id = ++self::$idCount;

   
  }

   function options_form(&$form, &$form_state) {
    $form['solr_host'] = array(
      '#type' => 'textfield',
      '#title' => t('Solr host'),
      '#default_value' => $this->solr_port,
      '#description' => t("The Solr server you wish to search on "),
      );
      $form['solr_port'] = array(
      '#type' => 'textfield',
      '#title' => t('Solr host'),
      '#default_value' => $this->solr_port,
      '#description' => t("The port of the solr server"),
      );
      $form['solr_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Solr path'),
      '#default_value' => $this->solr_path,
      '#description' => t("The path on the solr server "),
      );
      parent::options_form($form,$form_state);
   }
     
  function option_definition() {
    $options = parent::option_definition();
    $options['solr_host'] = array('default' => variable_get('apachesolr_host', 'localhost'));
    $options['solr_port'] = array('default' => variable_get('apachesolr_port', '8983'));
    $options['solr_path'] = array('default' => variable_get('apachesolr_path', '/solr'));
    
    return $options;
  }

}