<?php
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

  define ('TAB_HOME', 'home');
  define ('TAB_DOCS', 'docs');
  define ('TAB_DOWNLOADS', 'downloads');
  define ('TAB_SCREENSHOTS', 'screenshots');
  define ('TAB_SOURCE_CODE', 'source-code');
  define ('TAB_SUPPORT', 'support');
  define ('TAB_TRANSLATIONS', 'translations');

  include 'tabnav.inc';
  include 'release.inc';

  /**
   * ...
   */
  class Page {
    var $_title, $_charset;
    var $_description, $_keywords;
    var $_javascript, $_rssfeeds;
    var $_tab;
    var $_stablerelease;

    /**
     * Constructor
     */
    function __construct() {
      $this->_title = '';
      $this->_charset = 'utf-8';
      $this->_description = '';
      $this->_keywords = '';
      $this->_javascript = false;
      $this->_rssfeeds = array();
      $this->_tab = TAB_HOME;
      /* _Stable Release */
      $this->_stablerelease = new Release;
      $this->_stablerelease->setVersionNumber('2.16.40');
      $this->_stablerelease->setDate('2024-04-27');
      $this->_stablerelease->addDownload('setup.exe', __('x86 (32-bit)'), 'https://downloads.sourceforge.net/winmerge/WinMerge-2.16.40-Setup.exe', 9328920, 'd90ee78b59f07651372ec976f0a4da2e860129f04440380df7828c19eb5e1030');
      $this->_stablerelease->addDownload('setup64.exe', __('x64 (64-bit)'), 'https://downloads.sourceforge.net/winmerge/WinMerge-2.16.40-x64-Setup.exe', 9909272, 'c76bcfdd5025059f398e94f97d801a4a6cf52bef5b86f88209dcdffb28a141cd');
      $this->_stablerelease->addDownload('setup64peruser.exe', __('x64 (64-bit)'), 'https://downloads.sourceforge.net/winmerge/WinMerge-2.16.40-x64-PerUser-Setup.exe', 9909288, 'c2ee74723bddccc987587f6162558b4ad6e1b3750abdd83c197eee1a3f082ad9');
      $this->_stablerelease->addDownload('setuparm64.exe', __('ARM64 (64-bit)'), 'https://downloads.sourceforge.net/winmerge/WinMerge-2.16.40-ARM64-Setup.exe', 10733640, '6e85febd0c5867a831dd402325a94504975f0b9e668bb0d5f8f3c7262b149847');
      $this->_stablerelease->addDownload('exe.zip', __('x86 (32-bit)'), 'https://downloads.sourceforge.net/winmerge/winmerge-2.16.40-exe.zip', 12016671, 'd960c9749f6c74dc7f43c45328d60c7f6e376e3cb37854157e8ccc95c5445ba7');
      $this->_stablerelease->addDownload('exe64.zip', __('x64 (64-bit)'), 'https://downloads.sourceforge.net/winmerge/winmerge-2.16.40-x64-exe.zip', 12845561, '044d02b0b93c8ade880946a9afa1e476f4c9cdd740c299168b1e09878ed15337');
      $this->_stablerelease->addDownload('exearm64.zip', __('ARM64 (64-bit)'), 'https://downloads.sourceforge.net/winmerge/winmerge-2.16.40-ARM64-exe.zip', 12237390, 'ce10e978bc0f8445e7a66b84fb56d9893ece036d79e9c70719453c374e2559bc');
      $this->_stablerelease->addDownload('src.7z', '-', 'https://downloads.sourceforge.net/winmerge/winmerge-2.16.40-full-src.7z', 15569481, '487ae4276a526ddbe827aec8c2adda792b34fce2e4acc60fb4d3c4e793c11d65');
      $this->_stablerelease->setReleaseNotes('https://github.com/WinMerge/winmerge/releases/tag/v2.16.40');
      $this->_stablerelease->setKnownIssues('https://github.com/WinMerge/winmerge/releases/tag/v2.16.40#known-issues');
      $this->_stablerelease->setChangeLog('https://github.com/WinMerge/winmerge/blob/v2.16.40/Docs/Users/ChangeLog.md');
    }

    /**
     * set the title from the page
     */
    function setTitle($title) {
      $this->_title = $title;
    }

    /**
     * set the charset from the page
     */
    function setCharset($charset) {
      $this->_charset = $charset;
    }

    /**
     * set the description from the page
     */
    function setDescription($description) {
      $this->_description = $description;
    }

    /**
     * set the keywords from the page
     */
    function setKeywords($keywords) {
      $this->_keywords = $keywords;
    }

    /**
     * enable/disable JacaScript from the page
     */
    function setJavaScript($value) {
      $this->_javascript = $value;
    }

    /**
     * add RSS feed to the page head
     */
    function addRssFeed($url, $title = 'RSS') {
      $this->_rssfeeds[$url] = $title;
    }

    /**
     * set the tab from the page
     */
    function setTab($tab) {
      $this->_tab = $tab;
    }

    /**
     * print the head from the page
     */
    function printHead($title = '', $tab = '', $onload = '') {
      ob_start('ob_gzhandler'); //Use GZIP compression from PHP, since 1and1 don't support it from Apache!
      
      global $translations;
      
      $this->_title = $title;
      if ($tab != '') {
        $this->_tab = $tab;
      }
      $temp = "<!DOCTYPE html>\n";
      $temp .= "<html lang=\"" . $translations->getActiveLanguageId() . "\">\n\n";
      $temp .= "<head>\n";
      $temp .= "  <meta charset=\"" . $this->_charset . "\">\n";
      if ($this->_title != '') {
        $temp .= "  <title>" . $this->_title . " - WinMerge</title>\n";
      }
      else {
        $temp .= "  <title>WinMerge - " . __('You will see the difference…') ."</title>\n";
      }
      if ($this->_description != '') {
        $temp .= "  <meta name=\"description\" content=\"" . $this->_description . "\">\n";
      }
      if ($this->_keywords != '') {
        $temp .= "  <meta name=\"keywords\" content=\"" . $this->_keywords . "\">\n";
      }
      $temp .= "  <meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\" />\n";
      $temp .= "  <meta name=\"theme-color\" content=\"#fc0\" />\n";
      $temp .= "  <link rel=\"stylesheet\" type=\"text/css\" media=\"screen\" href=\"/engine/css/screen-v2.css\">\n";
      $temp .= "  <link rel=\"stylesheet\" type=\"text/css\" media=\"print\" href=\"/engine/css/print-v2.css\">\n";
      if ($this->_javascript == true || $onload != '') { //if JavaScript is needed...
        $temp .= "  <script src=\"/engine/javascript/winmerge.js\" type=\"text/javascript\"></script>\n";
      }
      $temp .= "  <!--[if lt IE 9]>\n";
      $temp .= "  <script src=\"/engine/javascript/html5shiv-printshiv.js\"></script>\n";
      $temp .= "  <![endif]-->\n";
      $temp .= "  <link rel=\"shortcut icon\" type=\"image/x-icon\" href=\"/favicon.ico\">\n";
      $temp .= "  <link rel=\"icon\" type=\"image/png\" href=\"/engine/images/icon-32x32.png\" sizes=\"32x32\">\n";
      $temp .= "  <link rel=\"icon\" type=\"image/png\" href=\"/engine/images/icon-48x48.png\" sizes=\"48x48\">\n";
      $temp .= "  <link rel=\"icon\" type=\"image/png\" href=\"/engine/images/icon-256x256.png\" sizes=\"256x256\">\n";
      $temp .= "  <link rel=\"apple-touch-icon-precomposed\" type=\"image/png\" href=\"/apple-touch-icon-precomposed.png\" sizes=\"180x180\">\n";
      foreach ($this->_rssfeeds as $rssurl => $rsstitle) { //for all RSS feeds...
        $temp .= "  <link rel=\"alternate\" type=\"application/rss+xml\" title=\"" . $rsstitle . "\" href=\"" . $rssurl . "\">\n";
      }
      $temp .= "  <link rel=\"canonical\" href=\"https://winmerge.org" . $translations->getLink($translations->getActiveLanguage(), true) . "\">\n";
      if ($translations->getLanguagesCount() > 1) { //if at least 2 languages exists...
        foreach ($translations->getLanguages() as $language) {
          $languageId = str_replace('_', '-', $language->getId());
          $languageLink = 'https://winmerge.org' . $translations->getLink($language, true);
          $temp .= "  <link rel=\"alternate\" href=\"" . $languageLink . "\" hreflang=\"" . $languageId . "\">\n";
        }
      }
      $temp .= "</head>\n\n";
      if ($onload != '')
        $temp .= "<body onload=\"".$onload."\">\n";
      else
        $temp .= "<body>\n";
      $temp .= "<div id=\"topwrap\">\n";
      $temp .= "  <header id=\"head\">\n";
      $temp .= "<div class=\"hgroup\">\n";
      $temp .= "  <h1>WinMerge</h1>\n";
      $temp .= "  <p class=\"tagline\">" . __('You will see the difference…') ."</p>\n";
      $temp .= "</div>\n";
      $temp .= "<p class=\"downloadlink\">" . $this->getDownloadNow(false) . "</p>\n";
      $temp .= "  </header>\n";
      $temp .= $this->getTabs();
      $temp .= "<div id=\"wrap\">\n";
      $temp .= "  <main id=\"content\">\n";
      $temp .= $this->getAds();
      print($temp);
    }

    /**
     * print the foot from the page
     */
    function printFoot() {
      global $translations;
      
      $temp = "  </main>\n";
      $temp .= "</div> <!-- #wrap -->\n";
      $temp .= "  <footer id=\"foot\">\n";
      $temp .= "    <div class=\"columns\">\n";
      $temp .= "      <div class=\"column\">\n";
      $temp .= "<h2>" . __('Change Language') ."</h2>\n";
      if ($translations->getLanguagesCount() > 1) { //if at least 2 languages exists...
        $temp .= "<ul class=\"languages\">\n";
        $languages = $translations->getLanguages();
        foreach ($languages as $language) { //for all languages...
          $link = "<a href=\"" . $translations->getLink($language, true) . "\" hreflang=\"" . $language->getId() . "\" title=\"" . __($language->getName()) .  "\">" . $language->getCultureName('&#8209;') . "</a>";
          if ($translations->isActiveLanguage($language)) { //if current language...
            $temp .= "  <li><strong>$link</strong></li>\n";
          }
          else { //if NOT current language...
            $temp .= "  <li>$link</li>\n";
          }
        }
        $temp .= "</ul> <!-- .languages -->\n";
      }
      $temp .= "      </div> <!-- .column -->\n";
      $temp .= "      <div class=\"column\">\n";
      $temp .= "<h2>" . __('Project Pages') ."</h2>\n";
      $temp .= "<ul>\n";
      $temp .= "  <li><a href=\"https://github.com/winmerge/winmerge\">GitHub</a></li>\n";
      $temp .= "  <li><a href=\"https://sourceforge.net/projects/winmerge\">SourceForge</a> <em>" . __('Archive') ."</em></li>\n";
      $temp .= "</ul>\n";
      $temp .= "      </div> <!-- .column -->\n";
      $temp .= "      <div class=\"column\">\n";
      $temp .= "<h2>" . __('Donate') ."</h2>\n";
      $temp .= "<p><a href=\"https://sourceforge.net/donate/index.php?group_id=13216\"><img src=\"/engine/images/project-support.jpg\" width=\"88\" height=\"32\" border=\"0\" alt=\"Donate\" title=\"Donate money to WinMerge\"></a></p>\n";
      $temp .= "      </div> <!-- .column -->\n";
      $temp .= "    </div> <!-- .columns -->\n";
      $temp .= "  </footer> <!-- #foot -->\n";
      $temp .= "</body>\n\n";
      $temp .= "</html>\n";
      print($temp);
    }

    /**
     * print a <h2> heading
     */
    function printHeading($title) {
      print("<h2>" . $title . "</h2>\n");
    }

    /**
     * print a <h2> heading with a RSS feed link
     */
    function printRssHeading($title, $rssfeedurl) {
      print("<h2>" . $title . " " . $this->getRssFeedLink($rssfeedurl) . "</h2>\n");
    }

    /**
     * print a <h3> heading
     */
    function printSubHeading($title) {
      print("<h3>" . $title . "</h3>\n");
    }

    /**
     * print a <h3> heading with link
     */
    function printLinkedSubHeading($title, $link) {
      print("<h3><a href=\"" . $link . "\">" . $title . "</a></h3>\n");
    }

    /**
     * print a <h3> heading with anchor
     */
    function printAnchorSubHeading($title, $anchor) {
      print("<h3><a name=\"" . $anchor . "\">" . $title . "</a></h3>\n");
    }

    /**
     * print a <h3> heading with a RSS feed link
     */
    function printRssSubHeading($title, $rssfeedurl) {
      print("<h3>" . $title . " " . $this->getRssFeedLink($rssfeedurl) . "</h3>\n");
    }

    /**
     * print a <h4> heading
     */
    function printSubSubHeading($title) {
      print("<h4>" . $title . "</h4>\n");
    }

    /**
     * print a paragraph
     */
    function printPara() {
      print("<p>");
      $numargs = func_num_args();
      $args = func_get_args();
      for ($i = 0; $i < $numargs; $i++) { //for all arguments...
        if ($i > 0) //if NOT first argument...
          print(' ' . $args[$i]);
        else //if first argument...
          print($args[$i]);
      }
      print("</p>\n");
    }

    /**
     * get the "Download Now!" link
     */
    function getDownloadNow($addparagraph = true) {
      $href = $this->_stablerelease->getDownload('setup.exe');
      $title = __('Version %1$s; %2$s MB', $this->_stablerelease->getVersionNumber(), $this->_stablerelease->getDownloadSizeMb('setup.exe'));
      
      $temp = "";
      if ($addparagraph) {
        $temp .= "<p>";
      }
      $temp .= "<a class=\"button is-large is-success\" href=\"{$href}\" title=\"{$title}\">" . __('Download Now!') . "</a>";
      if ($addparagraph) {
        $temp .= "</p>\n";
      }
      return $temp;
    }

    /**
     * print the "Download Now!" link
     */
    function printDownloadNow() {
      print($this->getDownloadNow());
    }

    /**
     * get a RSS feed link
     */
    function getRssFeedLink($url, $text = '') {
      $temp = "<a href=\"" . $url . "\"><img src=\"/engine/images/rss.png\" alt=\"RSS\" border=\"0\"></a>";
      if ($text != '') { //if WITH text...
        $temp .= " <a href=\"" . $url . "\"> " . $text . "</a>";
      }
      return $temp;
    }

    /**
     * print a RSS feed link
     */
    function printRssFeedLink($url, $text = '') {
      print($this->getRssFeedLink($url, $text));
    }

    /**
     * get the tabs menu from the page
     */
    function getTabs() {
      global $translations;
      
      /* Main Tabs */
      $tabs[0] = new Tab(TAB_HOME, $translations->prepareLink('/'), __('Home'), __('WinMerge Home'));
      $tabs[1] = new Tab(TAB_DOCS, $translations->prepareLink('/docs/'), __('Documentation'), __('WinMerge Documentation'));
      $tabs[2] = new Tab(TAB_DOWNLOADS, $translations->prepareLink('/downloads/'), __('Downloads'), __('WinMerge Downloads'));
      $tabs[3] = new Tab(TAB_SCREENSHOTS, $translations->prepareLink('/screenshots/'), __('Screenshots'), __('WinMerge Screenshots'));
      $tabs[4] = new Tab(TAB_SOURCE_CODE, $translations->prepareLink('/source-code/'), __('Source Code'), __('WinMerge Source Code'));
      $tabs[5] = new Tab(TAB_SUPPORT, $translations->prepareLink('/support/'), __('Support'), __('WinMerge Support'));
      $tabs[6] = new Tab(TAB_TRANSLATIONS, $translations->prepareLink('/translations/'), __('Translations'), __('WinMerge Translations'));

      $temp = "  <nav id=\"nav\">\n";
      $temp .= "<ul>\n";
      foreach ($tabs as $tab) { //for all tabs...
        if ($this->_tab == $tab->getId()) { //if current tab...
          $temp .= "  <li class=\"active\"><strong><a href=\"" . $tab->getLink() . "\" id=\"current\" title=\"" . $tab->getToolTipText() . "\">" . $tab->getTitle() . "</a></strong></li>\n";
        }
        else { //if NOT current tab...
          $temp .= "  <li><a href=\"" . $tab->getLink() . "\" title=\"" . $tab->getToolTipText() . "\">" . $tab->getTitle() . "</a></li>\n";
        }
      }
      $temp .= "</ul>\n";
      $temp .= "  </nav> <!-- #nav -->\n";
      $temp .= "</div> <!-- #topwrap -->\n";

      return $temp;
    }

    /**
     * get the ads to display on the page
     */
    function getAds() {
      $temp = "<div align=\"center\" id=\"ads\">\n";
      $temp .= "<script type=\"text/javascript\"><!--\n";
      $temp .= "google_ad_client = \"pub-1411904495533584\";\n";
      $temp .= "google_ad_width = 728;\n";
      $temp .= "google_ad_height = 90;\n";
      $temp .= "google_ad_format = \"728x90_as\";\n";
      $temp .= "google_ad_type = \"text\";\n";
      $temp .= "google_ad_channel =\"\";\n";
      $temp .= "google_color_border = \"FFCC00\";\n";
      $temp .= "google_color_bg = \"FFFFCC\";\n";
      $temp .= "google_color_link = \"0000FF\";\n";
      $temp .= "google_color_text = \"000000\";\n";
      $temp .= "google_color_url = \"008000\";\n";
      $temp .= "//--></script>\n";
      $temp .= "<script type=\"text/javascript\"\n";
      $temp .= "  src=\"https://pagead2.googlesyndication.com/pagead/show_ads.js\">\n";
      $temp .= "</script>\n";
      $temp .= "</div> <!-- #ads -->\n";
      return $temp;
    }

    /**
     * get the stable release
     */
    function getStableRelease() {
      return $this->_stablerelease;
    }
    
    /**
     * get the content (between <body> and </body>) from a HTML file
     */
    function getContentFromHtmlFile($filename, $patterns = '', $replacements = '') {
      $html = "";
      if (file_exists($filename) == true) { //if the file exists...
        $lines = file($filename);
        $linescount = sizeof($lines);
        
        $insidebody = false;
        for ($i = 0; $i < $linescount; $i++) { //for all lines...
          $line = $lines[$i];
          
          if ($insidebody == false) { //if OUTSIDE <body>...
            if (preg_match('#\<body#si', $line)) {
              $insidebody = true;
            }
          }
          else { //if INSIDE <body>...
            if (preg_match('#\</body>#si', $line)) {
              break;
            }
            if (($patterns != '') && ($replacements != '')) { //if text should be replaced...
              $line = preg_replace($patterns, $replacements, $line);
            }
            $html .= $line;
          }
        }
      }
      return $html;
    }
    
    
    /**
     * convert a (new) changelog file into html code
     */
    function convertChangeLog2Html($filename) {
      $html = "";
      if (file_exists($filename) == true) { //if the file exists...
        $html .= "<pre>\n";
        
        $lines = file($filename);
        $linescount = sizeof($lines);
        
        for ($i = 0; $i < $linescount; $i++) { //for all lines...
          $line = $lines[$i];
          
          $line = preg_replace('#(WinMerge [0-9]\.[0-9].*-.*\))#si', '<h3>\\1</h3>', $line);
          $line = preg_replace('#r(\d+)#si', '<a href="https://sourceforge.net/p/winmerge/code/\\1" target="_blank">r\\1</a>', $line);
          $line = preg_replace('#\#(\d{6,})#si', '<a href="https://sourceforge.net/support/tracker.php?aid=\\1" target="_blank">#\\1</a>', $line);
          $line = preg_replace('#patches:\#(\d+)#si', '<a href="https://winmerge.org/patch/\\1" target="_blank">#\\1</a>', $line);
          
          $html .= $line;
        }
        $html .= "</pre>\n";
      }
      return $html;
    }
  }
?>
