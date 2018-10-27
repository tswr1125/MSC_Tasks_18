using System;
using System.Collections.Specialized;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace ChengyuRobot
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ServicePointManager.ServerCertificateValidationCallback = delegate { return true; };
            comboBox1.SelectedIndex = 0;
        }
        public string doGet(string url)
        {
            WebClient client = new WebClient();
            byte[] res = client.DownloadData(url);
            string html = Encoding.UTF8.GetString(res);
            return html;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string input = textBox1.Text;
            if (!is4Ch(input)) MessageBox.Show("请输入四字汉字成语！");
            else
            {
                if (!isCh(input))
                {
                    MessageBox.Show("请输入正确的四字成语！");
                    return;
                }
                switch (comboBox1.SelectedIndex)
                {
                    case 0:
                        myAPI(input);
                        break;
                    case 1:
                        string res = doGet("http://i.itpk.cn/api.php?question=@cy" + textBox1.Text);
                        rtbLogs.AppendText(input + "-->" + res + "\n");
                        if (res.Length == 4) textBox1.Text = res;
                        break;
                }

            }
        }

        public void myAPI(string str)
        {
            string last = str.Substring(3);
            string uc = StringToUnicode(last);
            
            WebClient client = new WebClient();
            string html = doGet("https://chengyu.911cha.com/zi" + uc + "_1.html");
            html = ReplaceHtmlTagNWhite(html);
            if (html.Contains("没有找到相关成语"))
            {
                rtbLogs.AppendText(str + "-->未找到以"+ last+"开头成语！\n"); 
            }
            else
            {
                string reg = "(?<=〔).{4,6}(?=〕)";
                Regex r = new Regex(reg, RegexOptions.None);
                Match mc = r.Match(html);
                string dataStr = mc.Groups[0].Value;
                rtbLogs.AppendText(str + "-->"+dataStr + "\n");
                if (dataStr.Length == 4) textBox1.Text = dataStr;
            }
          
        }
        public bool is4Ch(string src)
        {
            string reg = "[\u4e00-\u9fa5]{4}";
            Regex r = new Regex(reg, RegexOptions.None);
            Match mc = r.Match(src);
            return (mc.Success);
            
        }

        public bool isCh(string src)
        {
            var html = doGet("https://xiaoxue.hujiang.com/cyu/search/0_"+src+"_"+src+"_0/");
            return (!html.Contains("暂无相关成语"));
        }

        public static string ReplaceHtmlTagNWhite(string html)
        {
            string strText = Regex.Replace(html, "<[^>]+>", "");
            strText = Regex.Replace(strText, "&[^;]+;", "");
            strText = strText.Replace(" ", "").Replace("\n", "");
            return strText;
        }


       

        //https://blog.csdn.net/nnsword/article/details/6023367 
        public static string StringToUnicode(string s)
        {
            char[] charbuffers = s.ToCharArray();
            byte[] buffer;
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < charbuffers.Length; i++)
            {
                buffer = System.Text.Encoding.Unicode.GetBytes(charbuffers[i].ToString());
                sb.Append(String.Format("{0:X2}{1:X2}", buffer[1], buffer[0]));
            }
            return sb.ToString();
        }  


    }
}
