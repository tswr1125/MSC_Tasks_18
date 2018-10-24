<?php
	include_once 'simple_html_dom.php';
	function query_url($char) {
		$ch = curl_init();
		curl_setopt($ch,CURLOPT_URL,'https://chengyu.911cha.com/');
		curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
		curl_setopt($ch,CURLOPT_POST,1);
		curl_setopt($ch,CURLOPT_POSTFIELDS,array('zi1'=>$char,'sotype'=>0));
		$ret = curl_exec($ch);
		$lpos = strpos($ret,"document.location.href=\"");
		$str = substr($ret,$lpos+24,13);
		if (substr($str,-4) != "html") return false;
		return 'https://chengyu.911cha.com/' . $str;
	}
	function query_cy($char) {
		$url = query_url($char);
		if ($url === false) return false;
		$html = new simple_html_dom();
		$html->load(file_get_contents($url));
		$ret = array();
		foreach ($html->find('a[class=\'green\']') as $element) {
			$tmp = strip_tags($element->plaintext);
			if (mb_substr($tmp,0,1) == $char && mb_strlen($tmp) == 4) array_push($ret,$tmp);
		}
		if (count($ret) == 0) return false;
		return $ret;
	}
	$last = "";
	while (1) {
		echo ">";
		$cur = trim(fgets(STDIN));
		while ( ($last != "" && mb_substr($cur,0,1) != $last) || mb_strlen($cur) != 4) {
			echo "<非法输入，请重试！\n";
			echo ">";
			$cur = trim(fgets(STDIN));
		}
		$query_result = query_cy(mb_substr($cur,-1,1));
		if ($query_result === false) {
			echo "<程序认输了😭\n";
			break;
		}
		echo '<' . $query_result[0] . "\n";
		$last = mb_substr($query_result[0],-1,1);
	}
?>