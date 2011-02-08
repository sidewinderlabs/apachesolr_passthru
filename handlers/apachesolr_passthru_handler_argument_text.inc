<?php
// $Id$
class apachesolr_passthru_handler_argument_text
  extends views_handler_argument {
  /**
   * Add argument to query.
   */
  public function query() {
    if (!empty($this->options['break_phrase'])) {
      $this->value = explode(',', $this->argument);
    }
    else {
      $this->value = array($this->argument);
    }
    $arg_value = array();
    foreach ($this->value as $facet_value) {
      $arg_value[] = apachesolr_views_query::escape_term($facet_value);
    }
    $this->query->add_filter($this->real_field, implode(" OR ", $arg_value), $this->options['not']);
    $this->query->set_query("*");
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['break_phrase'] = array('default' => FALSE);
    $options['not'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // allow for , delimited values
    $form['break_phrase'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow multiple terms per argument.'),
      '#description' => t('If selected, users can enter multiple arguments in the form of 1,2,3.'),
      '#default_value' => !empty($this->options['break_phrase']),
    );

    $form['not'] = array(
      '#type' => 'checkbox',
      '#title' => t('Exclude the argument'),
      '#description' => t('If selected, the numbers entered in the argument will be excluded rather than limiting the view.'),
      '#default_value' => !empty($this->options['not']),
    );
  }

  /**
   * Provide a list of default behaviors for this argument if the argument
   * is not present.
   *
   * Provide fewer methods that the standard. Remove summary views
   */
  function default_actions($which = NULL) {
    $defaults = array(
      'ignore' => array(
        'title' => t('Display all values'),
        'method' => 'default_ignore',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'not found' => array(
        'title' => t('Hide view / Page not found (404)'),
        'method' => 'default_not_found',
        'hard fail' => TRUE, // This is a hard fail condition
      ),
      'empty' => array(
        'title' => t('Display empty text'),
        'method' => 'default_empty',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'default' => array(
        'title' => t('Provide default argument'),
        'method' => 'default_default',
        'form method' => 'default_argument_form',
        'has default argument' => TRUE,
        'default only' => TRUE, // this can only be used for missing argument, not validation failure
      ),
    );

    if ($which) {
      if (!empty($defaults[$which])) {
        return $defaults[$which];
      }
    }
    else {
      return $defaults;
    }
  }
}
