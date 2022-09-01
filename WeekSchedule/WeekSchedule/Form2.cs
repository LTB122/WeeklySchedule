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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            InitSTT();
            InitMission();
        }

        //Var declaration
        static int stt = 0, missionstt = 0;
        static string sttstring="";

        GroupBox[] gbox = new GroupBox[1000];
        FlowLayoutPanel[] fpanel = new FlowLayoutPanel[1000];

        string[] Mission = new string[100000];
        string[] Temp = new string[100000];
        private void InitSTT()
        {
            if(!File.Exists("NumOfRole.txt"))
            {
                File.WriteAllText("NumOfRole.txt", "0");
                stt = 0;
            }
            else
            {
                sttstring = File.ReadAllText("NumOfRole.txt");
                stt = Convert.ToInt32(sttstring);
            }
        }

        private void InitMission()
        {
            string s;
            for (int i = 1; i <= stt; i++) 
            {
                s = File.ReadAllText("Role" + i.ToString() + "/Name.txt");
                CreateNewGb(i,s);
                InitNumOfMission(i);

                for (int j = 0; j < missionstt; j++)
                {
                    CreateNewMission(i, Mission[j],j);
                }

            }
        }

        private int RoleNum(string s)
        {
            foreach(GroupBox item in flowLayoutPanel1.Controls)
            {
                if (item.Text == s) return Convert.ToInt32(item.Name);
            }
            return -1;
        }

        private void CreateData(int n)
        {
            ///Save to Directory
            Directory.CreateDirectory("Role" + n.ToString());

            ///Save To File Name
            File.WriteAllText("Role" + n.ToString() + "/Name.txt", NameRole.Text);

            ///Save New Num of Mission
            File.WriteAllText("Role" + n.ToString() + "/NumOfMission.txt", "0");

            missionstt = 0;
        }

        private void CreateNewGb(int n, string s)
        {
            ///CreateNewGroupBox
            GroupBox gb = new GroupBox()
            {
                Name = n.ToString(),
                Text = s,
                Size = new Size(404, 252),
                ForeColor = Color.Teal
            };

            FlowLayoutPanel fp = new FlowLayoutPanel()
            {
                Name = n.ToString(),
                AutoScroll = true,
                Size = new Size(392, 216),
                Location = new Point(gb.Location.X + 10, gb.Location.Y + 25)
            };

            gbox[n] = gb;
            fpanel[n] = fp;

            gb.Controls.Add(fp);
            flowLayoutPanel1.Controls.Add(gb);
        }

        private void CreateNewMission(int n,string s, int i)
        {
            CheckBox ckb = new CheckBox()
            {
                AutoSize = true,
                Text = s,
                Name = n + "_" + i,
                ForeColor = Color.Black
            };

            ckb.CheckedChanged += Ckb_CheckedChanged;

            fpanel[n].Controls.Add(ckb);
        }

        private void Ckb_CheckedChanged(object? sender, EventArgs e)
        {
            CheckBox ckb = sender as CheckBox;

            ///Xulixau
            string s=ckb.Name,s1="";
            int n = 0, k = 0;
            for (int i = 0; i < s.Length; i++) 
            {
                if (s[i] != '_') s1 += s[i];
                else
                {
                    n = Convert.ToInt32(s1);
                    s1 = "";
                }
            }

            k = Convert.ToInt32(s1);
            
            InitNumOfMission(n);

            if (ckb.Checked)
            {
                int j = 0;
                for (int i = 0; i < missionstt; i++)
                {
                    if(i!=k)
                    {
                        Temp[j] = Mission[i];
                        j++;
                    }
                }

                missionstt--;
                for (int i = 0; i < missionstt; i++) Mission[i] = Temp[i];

            }
            else
            {
                Mission[missionstt] = ckb.Text;
                missionstt++;
            }

            UpdateMission(n);
        }

        private void UpdateSTT()
        {
            sttstring = stt.ToString();
            File.WriteAllText("NumOfRole.txt", sttstring);
        }

        private void UpdateMission(int n)
        {
            sttstring = missionstt.ToString();
            File.WriteAllText("Role" + n.ToString() + "/NumOfMission.txt", sttstring);

            ///Save to file Mission
            File.WriteAllLines("Role" + n.ToString() + "/Mission.txt", Mission);
        }

        private void InitNumOfMission(int n)
        {
            sttstring = File.ReadAllText("Role" + n.ToString() + "/NumOfMission.txt");
            missionstt = Convert.ToInt32(sttstring);

            if(File.Exists("Role" + n.ToString() + "/Mission.txt"))
                Mission = File.ReadAllLines("Role" + n.ToString() + "/Mission.txt");
        }

        private void NewWeek_Click(object sender, EventArgs e)
        {
            for (int i = 1; i <= stt; i++)
            {
                DirectoryInfo direct = new DirectoryInfo("Role" + i.ToString());
                if(direct.Exists) direct.Delete(true);
            }
            stt = 0;
            UpdateSTT();
            flowLayoutPanel1.Controls.Clear();
        }

        private void Addbtn_Click(object sender, EventArgs e)
        {
            ///Check NameRole & Mission
            if(NameRole.Text=="" || NewMission.Text=="")
            {
                MessageBox.Show("Hãy nhập tên vai trò và nhiệm vụ mới.", "Thông báo",
                    MessageBoxButtons.OK,MessageBoxIcon.Warning);
                return;
            }

            ///Add new namerole
            int kt=RoleNum(NameRole.Text);
            if(kt==-1)
            {
                stt++;
                CreateData(stt);
                CreateNewGb(stt,NameRole.Text);
                kt = stt;
                UpdateSTT();
            }

            InitNumOfMission(kt);

            CreateNewMission(kt, MissionTxt.Text + ", " + dateTimePicker1.Text,missionstt);

            Mission[missionstt] = MissionTxt.Text + ", " + dateTimePicker1.Text;
            
            missionstt++;
            UpdateMission(kt);
        }
    }
}
