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
            InitMissionSTT();
            InitMission();
        }

        //Var declaration
        static int stt = 0, missionstt = 0;
        static string sttstring="";

        GroupBox[] gbox = new GroupBox[1000];
        FlowLayoutPanel[] fpanel = new FlowLayoutPanel[1000];
        CheckBox[] ckbox = new CheckBox[100000]; 

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

        private void InitMissionSTT()
        {
            if (!File.Exists("NumOfMission.txt"))
            {
                File.WriteAllText("NumOfMission.txt", "0");
                missionstt = 0;
            }
            else
            {
                sttstring = File.ReadAllText("NumOfMission.txt");
                missionstt = Convert.ToInt32(sttstring);
            }
        }

        private void InitMission()
        {
            
        }

        private int RoleNum(string s)
        {
            foreach(GroupBox item in flowLayoutPanel1.Controls)
            {
                if (item.Text == s) return Convert.ToInt32(item.Name);
            }
            return -1;
        }

        private void CreateNewGb(int n)
        {
            ///Save to Directory
            if(!Directory.Exists("Role"+n.ToString()))  Directory.CreateDirectory("Role" + n.ToString());

            ///Save To File Name
            if(!File.Exists("Role" + n.ToString()+"/Name.txt"))
                File.WriteAllText("Role" + n.ToString() + "/Name.txt", NameRole.Text);
            
            ///CreateNewGroupBox
            GroupBox gb = new GroupBox()
            {
                Name = n.ToString(),
                Text = NameRole.Text,
                Size = new Size(404, 252)
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

        private void CreateNewMission(int n)
        {
            CheckBox ckb = new CheckBox()
            {
                AutoSize = true,
                Text = MissionTxt.Text + ", " + dateTimePicker1.Text
            };

            ///Save to file Mission
            if (!File.Exists("Role" + n.ToString() + "/Mission.txt"))
                File.WriteAllText("Role" + n.ToString() + "/Mission.txt", ckb.Text);
            else File.AppendAllText("Role" + n.ToString() + "/Mission.txt", ckb.Text);

            ckbox[missionstt] = ckb;
            fpanel[n].Controls.Add(ckb);
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
                CreateNewGb(stt);
                kt = stt;
            }
            missionstt++;
            CreateNewMission(kt);
        }
    }
}
