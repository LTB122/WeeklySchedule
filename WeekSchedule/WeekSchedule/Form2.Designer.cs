namespace WeekSchedule
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.NewMission = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.Addbtn = new System.Windows.Forms.Button();
            this.MissionTxt = new System.Windows.Forms.TextBox();
            this.NameRole = new System.Windows.Forms.TextBox();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.NewMission.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // NewMission
            // 
            this.NewMission.Controls.Add(this.panel1);
            this.NewMission.Location = new System.Drawing.Point(12, 12);
            this.NewMission.Name = "NewMission";
            this.NewMission.Size = new System.Drawing.Size(512, 150);
            this.NewMission.TabIndex = 0;
            this.NewMission.TabStop = false;
            this.NewMission.Text = "Nhiệm vụ mới";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.dateTimePicker1);
            this.panel1.Controls.Add(this.Addbtn);
            this.panel1.Controls.Add(this.MissionTxt);
            this.panel1.Controls.Add(this.NameRole);
            this.panel1.Location = new System.Drawing.Point(6, 30);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(500, 114);
            this.panel1.TabIndex = 0;
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(194, 3);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(300, 31);
            this.dateTimePicker1.TabIndex = 3;
            // 
            // Addbtn
            // 
            this.Addbtn.Location = new System.Drawing.Point(183, 77);
            this.Addbtn.Name = "Addbtn";
            this.Addbtn.Size = new System.Drawing.Size(112, 34);
            this.Addbtn.TabIndex = 2;
            this.Addbtn.Text = "Thêm";
            this.Addbtn.UseVisualStyleBackColor = true;
            this.Addbtn.Click += new System.EventHandler(this.Addbtn_Click);
            // 
            // MissionTxt
            // 
            this.MissionTxt.Location = new System.Drawing.Point(3, 40);
            this.MissionTxt.Name = "MissionTxt";
            this.MissionTxt.PlaceholderText = "Nhiệm vụ";
            this.MissionTxt.Size = new System.Drawing.Size(491, 31);
            this.MissionTxt.TabIndex = 1;
            // 
            // NameRole
            // 
            this.NameRole.Location = new System.Drawing.Point(3, 3);
            this.NameRole.Name = "NameRole";
            this.NameRole.PlaceholderText = "Tên vai trò";
            this.NameRole.Size = new System.Drawing.Size(185, 31);
            this.NameRole.TabIndex = 0;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.AutoScroll = true;
            this.flowLayoutPanel1.AutoSize = true;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(12, 168);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(1035, 314);
            this.flowLayoutPanel1.TabIndex = 1;
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1059, 494);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.NewMission);
            this.Name = "Form2";
            this.Text = "Form2";
            this.NewMission.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private GroupBox NewMission;
        private Panel panel1;
        private Button Addbtn;
        private TextBox MissionTxt;
        private TextBox NameRole;
        private FlowLayoutPanel flowLayoutPanel1;
        private DateTimePicker dateTimePicker1;
    }
}