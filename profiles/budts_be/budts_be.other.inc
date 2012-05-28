<?php

function budts_be_install_other() {
  // set up a nice alias for the tagadelic tagcloud
  $path = array('source' => 'tagadelic/chunk/1',
                'alias' => 'tag',);
  path_save($path);
}

