using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WeekSchedule
{
    public partial class Form3 : Form
    {
        //Var
        static int numTar = 0;
        string[] TarS = new string[10000];
        GroupBox[] gbx = new GroupBox[1000];
        FlowLayoutPanel[] flp = new FlowLayoutPanel[1000];
        static bool isChange = false;
        CheckBox[] ckbx = new CheckBox[10000];
        string content = "";

        public Form3()
        {
            InitializeComponent();
            InitDirect();
        }

        private string split(string s)
        {
            string s2 = "";
            for(int i=0;i<s.Length;i++) 
                if (s[i]==',')
                {
                    s2 = s.Substring(0, i + 1);
                    content = s.Substring(i + 2);
                    break;
                }

            return s2;
        }

        private int Cmp(string s1, string s2)
        {
            if (s1 == "") return 2;
            if (s2 == "") return 1;

            DateTime date = Convert.ToDateTime(split(s1));
            DateTime date2 = Convert.ToDateTime(split(s2));

            if (date < date2) return 0;
            if (date > date2) return 1;
            return 2;
        }

        private void Sort(int l, int r)
        {
            int mid = (l + r) / 2;
            int i = l, j = r;
            while(i<j)
            {
                while (Cmp(TarS[i], TarS[mid])==0) i++;
                while (Cmp(TarS[mid], TarS[j])==0) j--;

                if(i<=j)
                {
                    string temp = TarS[i];
                    TarS[i] = TarS[j];
                    TarS[j] = temp;

                    i++; j--;
                }
            }

            if (l < j) Sort(l, j);
            if (r > i) Sort(i, r);
        }

        private void UpdateTar()
        {
            Sort(0, numTar - 1);
        }

        private void CreateGb(int i, DateTime date)
        {
            gbx[i] = new GroupBox()
            {
                Name = date.Month + "/" + date.Year,
                Text = date.Month + "/" + date.Year,
                Size = new Size(400, 250),
                ForeColor = Color.DarkOliveGreen
            };
            flp[i] = new FlowLayoutPanel();
            flp[i].Size = new Size(380, 220);
            flp[i].Location = new Point(10, 25);
            flp[i].AutoScroll = true;

            gbx[i].Controls.Add(flp[i]);
            flowLayoutPanel1.Controls.Add(gbx[i]);
        }

        private void CreateCkb(int i, string s, int k)
        {
            CheckBox ckb = new CheckBox();
            ckb.Name = k.ToString();
            ckb.Text = s;
            ckb.CheckedChanged += Ckb_CheckedChanged;
            ckb.AutoSize = true;
            ckb.ForeColor = Color.Black;

            flp[i].Controls.Add(ckb);
        }

        private void ShowData()
        {
            int j = -1;
            for(int i=0;i<numTar;i++)
            {
                DateTime date = Convert.ToDateTime(split(TarS[i]));
                if (j==-1 || gbx[j].Name!=date.Month+"/"+date.Year)
                {
                    j++;
                    CreateGb(j, date);
                }
                CreateCkb(j,content,i);
            }
        }

        private void InitDirect()
        {
            if (!Directory.Exists("Target")) Directory.CreateDirectory("Target");
            if (!File.Exists("Target/NumOfTar.txt")) File.WriteAllText("Target/NumOfTar.txt", "0");

            string s = File.ReadAllText("Target/NumOfTar.txt");
            numTar = Convert.ToInt32(s);

            if (File.Exists("Target/Tar.txt"))
                TarS = File.ReadAllLines("Target/Tar.txt");
            isChange = false;

            ShowData();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text=="")
            {
                MessageBox.Show("enter target");
                return;
            }
            DateTime date = dateTimePicker1.Value;

            string s = date.Date.ToString();

            TarS[numTar] = s + ", " + textBox1.Text;
            numTar++;

            bool find = false;
            int i = 0;
            foreach(GroupBox item in flowLayoutPanel1.Controls)
            {
                DateTime date2 = Convert.ToDateTime(item.Name);
                if (date2.Year > date.Year) break;
                else
                {
                    if (date2.Year == date.Year && date2.Month > date.Month) break;
                }

                if(date.Month==date2.Month && date2.Year==date.Year)
                {
                    find = true;
                    CreateCkb(i,textBox1.Text,numTar-1);
                }
                i++;
            }

            if(!find)
            {
                CreateGb(i, date);
                CreateCkb(i,textBox1.Text,numTar-1);
            }
        }

        private void Ckb_CheckedChanged(object? sender, EventArgs e)
        {
            isChange = true;
            CheckBox ckb = sender as CheckBox;
            int n = Convert.ToInt32(ckb.Name);

            if (ckb.Checked) TarS[n] += ",altx";
            else TarS[n] = TarS[n].Substring(0, TarS[n].Length - 5);
        }



        private void Form3_FormClosed(object sender, FormClosedEventArgs e)
        {
            UpdateTar();
            if (isChange)
            {
                string[] Temp = new string[100000];

                int j = 0;
                int d = 0;
                for (int i = 0; i < numTar; i++)
                {
                    string s = TarS[i].Substring(TarS[i].Length - 5);
                    if (s != ",altx")
                    {
                        Temp[j] = TarS[i];
                        j++;
                    }
                    else d++;
                    TarS[i] = "";
                }

                numTar -= d;

                for (int i = 0; i < numTar; i++) TarS[i] = Temp[i];
            }
            File.WriteAllText("Target/NumOfTar.txt", numTar.ToString());
            File.WriteAllLines("Target/Tar.txt", TarS);
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!isChange) return;
            DialogResult result = MessageBox.Show("Bạn có chắc muốn lưu những thay đổi?", "Thông báo", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes) isChange = true;
            else isChange = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            this.Hide();
            f2.ShowDialog();
            this.Show();
        }
    }
}
