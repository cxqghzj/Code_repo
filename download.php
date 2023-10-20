<?php
$cid = $argv[1];
$cookie = "login=%5B%22admin%22%2C%22b6ffae533c2bd83e14db7f309d8b1b60%22%5D; connect.sid=s%3Ay2sXrylC7qxTRxlQUkbLejhAieF9qZeL.UUQJrq2chDqWDitGxSXkEco%2F7vzgGsKL7vqC0cJyB9U";
$contest_url = "http://10.1.143.113/contest/$cid/edit";

function geturl($url, $cookie){
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE); 
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE); 
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_COOKIE, $cookie);
    $output = curl_exec($ch);
    curl_close($ch);
    return $output;
}

function posturl($url, $data, $cookie){
    $data = json_encode($data);    
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, FALSE);
    curl_setopt($curl, CURLOPT_POST, 1);
    curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_COOKIE, $cookie);
    $output = curl_exec($curl);
    curl_close($curl);
}

class Request {
    protected $bar;
    // 是否下载完成
    protected $downloaded = false;
    public function __construct() {
        require_once "CliProgressBar.php";
        // 初始化一个进度条
        $this->bar = new CliProgressBar(100);
        $this->bar->display();
        $this->bar->setColorToGreen();
    }

    function download($url, $cookie, $filepath) {
        $ch = curl_init();
        // 从配置文件中获取根路径
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 0);
        // 开启进度条
        curl_setopt($ch, CURLOPT_NOPROGRESS, 0);
        curl_setopt($ch, CURLOPT_COOKIE, $cookie);
        $fp = fopen($filepath, 'w');
        curl_setopt($ch, CURLOPT_WRITEFUNCTION, function($ch, $str) use($fp) {
            $len = strlen($str);
            fwrite($fp, $str);
            return $len;
        });
        // 进度条的触发函数
        curl_setopt($ch, CURLOPT_PROGRESSFUNCTION, array($this, 'progress'));
        // ps: 如果目标网页跳转，也跟着跳转
        if (false === ($stream = curl_exec($ch))) 
            throw new \Exception(curl_errno($ch));
        $this->bar->progress(100);
        curl_close($ch);
    }

    /**
    * 进度条下载.
    *
    * @param $ch
    * @param $countDownloadSize 总下载量
    * @param $currentDownloadSize 当前下载量
    * @param $countUploadSize
    * @param $currentUploadSize
    */
    public function progress($ch, $countDownloadSize, $currentDownloadSize, $countUploadSize, $currentUploadSize) {
        // 等于 0 的时候，应该是预读资源不等于0的时候即开始下载
        // 这里的每一个判断都是坑，多试试就知道了
        if (0 === $countDownloadSize) return false;
        // 有时候会下载两次，第一次很小，应该是重定向下载
        if ($countDownloadSize > $currentDownloadSize) $this->downloaded = false;
        // 已经下载完成还会再发三次请求
        else if ($this->downloaded) return false;
        // 两边相等下载完成并不一定结束，
        else if ($currentDownloadSize === $countDownloadSize) return false;
        // 开始计算
        $bar = $currentDownloadSize / $countDownloadSize * 100;
        $this->bar->progress(round($bar, 0));
    }
};

/**
 * zip解压方法
 * @param string $filePath 压缩包所在地址
 * @param string $path 解压路径
 * @return bool
 */
function unzip($filePath, $path) {
    if (empty($path) || empty($filePath)) {
        return false;
    }

    $zip = new ZipArchive();

    if ($zip->open($filePath) === true) {
        $zip->extractTo($path);
        $zip->close();
        return true;
    } else {
        return false;
    }
}

$html = geturl($contest_url, $cookie);
preg_match_all('/<div[^>]*class="field"[^>]*>(.*?) <\/div>/is', $html, $match);
$match = $match[1]; $info = "";
$info .= "Contest Info: \n";
preg_match_all('/<input.*?value="(.*?)".*?>/is', $match[0], $array);
$info .= "Title: " . $array[1][0] . "\n";
preg_match_all('/<input.*?value="(.*?)".*?>/is', $match[1], $array);
$info .= "Subtitle: " . $array[1][0] . "\n";
preg_match_all('/<option.*?value="(.*?)".*?>(.*?)<\/option>/is', $match[2], $array);
$pid = array();
for ($i = 0; $i < count($array[1]); $i++) $pid[$i] = $array[1][$i];
$info .= "Problems: "; 
for ($i = 0; $i < count($array[2]); $i++) $info .= "[". $array[2][$i] . "], ";
$info .= "\n";
preg_match_all('/<option.*?value="(.*?)".*?>(.*?)<\/option>/is', $match[3], $array);
$info .= "Admins: "; 
for ($i = 0; $i < count($array[1]); $i++) $info .= "[". $array[2][$i] . "(uid = " . $array[1][$i] . ")], ";
$info .= "\n";
$info .= "Type: ";
if (stripos($match[4], "checked=\"checked\"") !== false) $info .= "NOI\n";
if (stripos($match[5], "checked=\"checked\"") !== false) $info .= "IOI\n";
if (stripos($match[6], "checked=\"checked\"") !== false) $info .= "ICPC\n";
preg_match_all('/<input.*?value="(.*?)".*?>/is', $match[7], $array);
$info .= "Ranking Param: " . $array[1][0] . "\n";
preg_match_all('/<textarea.*?>(.*?)<\/textarea>/is', $match[8], $array);
$content = $array[1][0];
$array2 = explode("\n", $content);
$info .= "Information: \n";
for ($i = 0; $i < count($array2); $i++) {
    $x = $array2[$i]; $x = trim($x);
    if ($x != "") $info .= $x . "\n";
}
preg_match_all('/<input.*?value="(.*?)".*?>/is', $match[9], $array);
$info .= "Start Time: " . $array[1][0] . "\n";
preg_match_all('/<input.*?value="(.*?)".*?>/is', $match[10], $array);
$info .= "End Time: " . $array[1][0] . "\n";
echo $info;
@mkdir("./contest/$cid");
$fp = fopen("./contest/$cid/readme.md", "w");
fwrite($fp, $info);
fclose($fp);
for ($i = 0; $i < count($pid); $i++) {
    echo "\n";
    echo "Problem Info: \n";
    $problem_url = "http://10.1.143.113/problem/" . $pid[$i] . "/edit";
    $html = geturl($problem_url, $cookie);
    preg_match_all('/<input.*?value="(.*?)".*?>/is', $html, $match);
    $match = $match[1]; $info = "";
    $info .= "# T" . ($i + 1) . " " . $match[1] . "\n\n";
    echo "ID: " . $match[0] . "\n";
    echo "Title: " . $match[1] . "\n";
    preg_match_all('/<textarea.*?>(.*?)<\/textarea>/is', $html, $match);
    $match = $match[1]; 
    $info .= "## Description\n\n" . $match[0] . "\n\n";
    echo "Description: \n" . $match[0] . "\n";
    $info .= "## Input\n\n" . $match[1] . "\n\n";
    echo "Input: \n" . $match[1] . "\n";
    $info .= "## Output\n\n" . $match[2] . "\n\n";
    echo "Output: \n" . $match[2] . "\n";
    $info .= "## Sample\n\n" . $match[3] . "\n\n";
    echo "Sample: \n" . $match[3] . "\n";
    $info .= "## Hint\n\n" . $match[4] . "\n\n";
    echo "Hint: \n" . $match[4] . "\n";
    
    echo "Downloading Problem $cid-" . ($i + 1) . "(pid = " . $pid[$i] . ")\n";
    $dir_path = "./contest/$cid/$cid-" . ($i + 1) . "(pid=" . $pid[$i] . ")";
    @mkdir($dir_path);
    $file_path = "./contest/$cid/$cid-" . ($i + 1) . "(pid=" . $pid[$i] . ")/problem.md";
    $fp = fopen($file_path, "w");
    fwrite($fp, $info);
    fclose($fp);

    $data_url = "http://10.1.143.113/problem/" . $pid[$i] . "/testdata/download";
    $file_path = "./contest/$cid/$cid-" . ($i + 1) . "(pid=" . $pid[$i] . ")/data.zip";
    (new Request)->download($data_url, $cookie, $file_path);
    echo "\n";
    echo "Extracting Problem Data $cid-" . ($i + 1) . "(pid = " . $pid[$i] . ")\n";
    unzip(realpath($file_path), realpath($dir_path));
}
echo "\n";
?>