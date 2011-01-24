<?php
// $Id$
class apachesolr_passthru_handler_filter_text
  extends views_handler_filter_string {

  /**
   * override query().
   */
  function query() {
    if ($this->operator == '!=') {
      $field = "NOT " . $this->value;
    }
    else {
      $field = $this->value;
    }
    $this->query->add_filter($this->real_field, $field);
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['case']);

  }

  /**
   * Override the operators
   */
  function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Is equal to'),
        'short' => t('='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'short' => t('!='),
        'method' => 'op_equal',
        'values' => 1,
      ),
    );
    return $operators;
  }
}
