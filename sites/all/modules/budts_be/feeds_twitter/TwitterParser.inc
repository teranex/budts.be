<?php

module_load_include('inc', 'feeds', 'plugins/FeedsSyndicationParser');

class TwitterParser extends FeedsSyndicationParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
      $result = parent::parse($source, $fetcher_result);

      foreach ($result->items as &$item) {
          $item['tags'] = $this->_parseHashTags($item['title']);
          $item['title'] = $item['description'] = $item['body'] = $this->_removeUsernameFromTweet($item['title']);
      }

      return $result;
  }

  private function _parseHashTags($text) {
      $matches = array();
      preg_match_all('/(^|\s)#(\w+)/', $text, $matches);
      return $matches[2];
  }

  private function _removeUsernameFromTweet($text) {
      $matches = array();
      preg_match('/^\w+:\s+(.*)/', $text, $matches);
      return $matches[1];
  }
}
