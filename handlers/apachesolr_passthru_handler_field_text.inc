<?php
// $Id$
class apachesolr_passthru_handler_field_text
  extends views_handler_field {

  function query() {
    $this->field_alias = $this->query->add_solr_field($this->options['field']);
  }
}
