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
            InitDataDirectory();
            InitSTT();
            InitWeek();
            InitMission();
        }

        //Var declaration
        static int stt = 0, missionstt = 0;
        static string sttstring="";
        static bool isChange = false;

        GroupBox[] gbox = new GroupBox[1000];
        FlowLayoutPanel[] fpanel = new FlowLayoutPanel[1000];

        string[] Mission = new string[100000];
        string[] Temp = new string[100000];

        private void InitDataDirectory()
        {
            if (!Directory.Exists("Data")) Directory.CreateDirectory("Data");
        }

        private void InitSTT()
        {
            if(!File.Exists("Data/NumOfRole.txt"))
            {
                File.WriteAllText("Data/NumOfRole.txt", "0");
                stt = 0;
            }
            else
            {
                sttstring = File.ReadAllText("Data/NumOfRole.txt");
                stt = Convert.ToInt32(sttstring);
            }
            isChange = false;
        }

        GroupBox[] gbweek = new GroupBox[7];
        FlowLayoutPanel[] fpweek = new FlowLayoutPanel[7];

        private int  Daytoint(string k)
        {
            switch (k)
            {
                case " Monday": return 0;
                case " Tuesday": return 1;
                case " Wednesday": return 2;
                case " Thursday": return 3;
                case " Friday": return 4;
                case " Saturday": return 5;
                default: return 6;

            }
        }

        private string Day(int k)
        {
            switch(k)
            {
                case 0: return "Monday";
                case 1: return "Tuesday";
                case 2: return "Wednesday";
                case 3: return "Thursday";
                case 4: return "Friday";
                case 5: return "Saturday";
                default: return "Sunday";

            }
        }

        private void InitWeek()
        {
            for(int i = 0; i < 7; i++)
            {
                gbweek[i] = new GroupBox()
                {
                    Text = Day(i),
                    Size = new Size(261, 370),
                    ForeColor = Color.Teal
                };
                
                fpweek[i] = new FlowLayoutPanel()
                {
                    AutoScroll = true,
                    Location = new Point(gbweek[i].Location.X + 10, gbweek[i].Location.Y + 25),
                    Size = new Size(249,330),
                };

                gbweek[i].Controls.Add(fpweek[i]);
                flowLayoutPanel2.Controls.Add(gbweek[i]);
            }
        }

        static string s2 = "";

        private string GetDay(string s)
        {
            s2 = "";
            string s1 = "";
            int comma = 0;

            for (int i = s.Length - 1; i > -1; i--) 
            {
                if (s[i] == ',')
                {
                    comma++;
                    if (comma <= 3) continue;
                }
                if (comma > 1 && comma < 3) s1 = s[i] + s1;
                if (comma >= 3) s2 = s[i] + s2;
            }

            return s1;
        }

        private void AddMissiontoCal(int k)
        {
            s2 = "- " + s2;
            Label lb = new Label()
            {
                Text = s2,
                AutoSize = true,
                ForeColor= Color.Black
            };
            fpweek[k].Controls.Add(lb);
        }

        private void InitMission()
        {
            string s;
            int z = 0;
            for (int i = 1; i <= stt; i++) 
            {
                s = File.ReadAllText("Data/Role" + i.ToString() + "/Name.txt");
                CreateNewGb(i,s);
                InitNumOfMission(i);

                for (int j = 0; j < missionstt; j++)
                {
                    CreateNewMission(i, Mission[j],j);
                    int k = Daytoint(GetDay(Mission[j]));
                    AddMissiontoCal(k);
                }

                if (missionstt <= 0)
                {
                    flowLayoutPanel1.Controls.Remove(gbox[i]);
                    z++;
                }
            }

            if (z >= stt) Getreadyfornewweek();
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
            Directory.CreateDirectory("Data/Role" + n.ToString());

            ///Save To File Name
            File.WriteAllText("Data/Role" + n.ToString() + "/Name.txt", NameRole.Text);

            ///Save New Num of Mission
            File.WriteAllText("Data/Role" + n.ToString() + "/NumOfMission.txt", "0");

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
            isChange = true;
        }

        private void UpdateSTT()
        {
            sttstring = stt.ToString();
            File.WriteAllText("Data/NumOfRole.txt", sttstring);
        }

        private void UpdateMission(int n)
        {
            sttstring = missionstt.ToString();
            File.WriteAllText("Data/Role" + n.ToString() + "/NumOfMission.txt", sttstring);

            ///Save to file Mission
            File.WriteAllLines("Data/Role" + n.ToString() + "/Mission.txt", Mission);
        }

        private void InitNumOfMission(int n)
        {
            sttstring = File.ReadAllText("Data/Role" + n.ToString() + "/NumOfMission.txt");
            missionstt = Convert.ToInt32(sttstring);

            if(File.Exists("Data/Role" + n.ToString() + "/Mission.txt"))
                Mission = File.ReadAllLines("Data/Role" + n.ToString() + "/Mission.txt");
        }

        private void Getreadyfornewweek()
        {
            for (int i = 1; i <= stt; i++)
            {
                DirectoryInfo direct = new DirectoryInfo("Data/Role" + i.ToString());
                if (direct.Exists) direct.Delete(true);
            }
            stt = 0;
            UpdateSTT();
            flowLayoutPanel1.Controls.Clear();

            for (int i = 0; i < 7; i++) fpweek[i].Controls.Clear();
        }

        private void NewWeek_Click(object sender, EventArgs e)
        {
            Getreadyfornewweek();
        }

        private void DeleteMission()
        {
            for (int i = 1; i <= stt; i++)
            {
                int j = 0, k = 0;
                InitNumOfMission(i);
                foreach (CheckBox item in fpanel[i].Controls)
                {
                    if (!item.Checked)
                    {
                        Temp[k] = Mission[j];
                        k++;
                    }
                    else missionstt--;
                    Mission[j] = "";
                    j++;
                }

                for (int h = 0; h < missionstt; h++) Mission[h] = Temp[h];
                UpdateMission(i);
            }
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(isChange)
            {
                DialogResult result = MessageBox.Show("Bạn có muốn lưu những thay đổi không?",
                    "Thông báo", MessageBoxButtons.YesNo);
                switch(result)
                {
                    case DialogResult.Yes: DeleteMission();
                        break;
                    case DialogResult.No:
                        break;
                }

            }
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

            int k = Daytoint(GetDay(MissionTxt.Text + ", " + dateTimePicker1.Text));
            AddMissiontoCal(k);

            Mission[missionstt] = MissionTxt.Text + ", " + dateTimePicker1.Text;
            
            missionstt++;
            UpdateMission(kt);
        }
    }
}
