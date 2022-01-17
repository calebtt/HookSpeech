namespace HookSpeechSharp
{
    partial class HssMainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(HssMainForm));
            this.lblTopText = new System.Windows.Forms.Label();
            this.btnToggleEnabled = new System.Windows.Forms.Button();
            this.lblAlphabetText = new System.Windows.Forms.Label();
            this.tbxAlphabetChars = new System.Windows.Forms.TextBox();
            this.grpAlphabetDetails = new System.Windows.Forms.GroupBox();
            this.btnUpdateAlphabet = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lblTopText
            // 
            this.lblTopText.AutoSize = true;
            this.lblTopText.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.lblTopText.Location = new System.Drawing.Point(36, 24);
            this.lblTopText.Name = "lblTopText";
            this.lblTopText.Size = new System.Drawing.Size(423, 21);
            this.lblTopText.TabIndex = 0;
            this.lblTopText.Text = "To disable the translation temporarily, use the button below.";
            // 
            // btnToggleEnabled
            // 
            this.btnToggleEnabled.BackColor = System.Drawing.SystemColors.ControlLight;
            this.btnToggleEnabled.FlatAppearance.BorderColor = System.Drawing.Color.Olive;
            this.btnToggleEnabled.FlatAppearance.MouseDownBackColor = System.Drawing.Color.BurlyWood;
            this.btnToggleEnabled.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnToggleEnabled.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.btnToggleEnabled.Location = new System.Drawing.Point(122, 59);
            this.btnToggleEnabled.Name = "btnToggleEnabled";
            this.btnToggleEnabled.Size = new System.Drawing.Size(251, 29);
            this.btnToggleEnabled.TabIndex = 1;
            this.btnToggleEnabled.TabStop = false;
            this.btnToggleEnabled.Text = "Disable";
            this.btnToggleEnabled.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.btnToggleEnabled.UseVisualStyleBackColor = false;
            this.btnToggleEnabled.Click += new System.EventHandler(this.btnToggleEnabled_Click);
            // 
            // lblAlphabetText
            // 
            this.lblAlphabetText.AutoSize = true;
            this.lblAlphabetText.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.lblAlphabetText.Location = new System.Drawing.Point(12, 100);
            this.lblAlphabetText.Name = "lblAlphabetText";
            this.lblAlphabetText.Size = new System.Drawing.Size(476, 21);
            this.lblAlphabetText.TabIndex = 2;
            this.lblAlphabetText.Text = "To change the alphabet which characters are mapped to, edit below.";
            // 
            // tbxAlphabetChars
            // 
            this.tbxAlphabetChars.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbxAlphabetChars.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.tbxAlphabetChars.Location = new System.Drawing.Point(12, 136);
            this.tbxAlphabetChars.Name = "tbxAlphabetChars";
            this.tbxAlphabetChars.Size = new System.Drawing.Size(476, 29);
            this.tbxAlphabetChars.TabIndex = 3;
            this.tbxAlphabetChars.Text = "[error]";
            // 
            // grpAlphabetDetails
            // 
            this.grpAlphabetDetails.Location = new System.Drawing.Point(57, 171);
            this.grpAlphabetDetails.Name = "grpAlphabetDetails";
            this.grpAlphabetDetails.Size = new System.Drawing.Size(381, 83);
            this.grpAlphabetDetails.TabIndex = 4;
            this.grpAlphabetDetails.TabStop = false;
            this.grpAlphabetDetails.Text = "Alphabet Details";
            this.grpAlphabetDetails.Visible = false;
            // 
            // btnUpdateAlphabet
            // 
            this.btnUpdateAlphabet.BackColor = System.Drawing.SystemColors.ControlLight;
            this.btnUpdateAlphabet.FlatAppearance.BorderColor = System.Drawing.Color.Olive;
            this.btnUpdateAlphabet.FlatAppearance.MouseDownBackColor = System.Drawing.Color.BurlyWood;
            this.btnUpdateAlphabet.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnUpdateAlphabet.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.btnUpdateAlphabet.Location = new System.Drawing.Point(122, 267);
            this.btnUpdateAlphabet.Margin = new System.Windows.Forms.Padding(3, 10, 3, 3);
            this.btnUpdateAlphabet.Name = "btnUpdateAlphabet";
            this.btnUpdateAlphabet.Size = new System.Drawing.Size(251, 29);
            this.btnUpdateAlphabet.TabIndex = 5;
            this.btnUpdateAlphabet.TabStop = false;
            this.btnUpdateAlphabet.Text = "Update Alphabet";
            this.btnUpdateAlphabet.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.btnUpdateAlphabet.UseVisualStyleBackColor = false;
            this.btnUpdateAlphabet.Click += new System.EventHandler(this.btnUpdateAlphabet_Click);
            // 
            // HssMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ClientSize = new System.Drawing.Size(516, 315);
            this.Controls.Add(this.btnUpdateAlphabet);
            this.Controls.Add(this.grpAlphabetDetails);
            this.Controls.Add(this.tbxAlphabetChars);
            this.Controls.Add(this.lblAlphabetText);
            this.Controls.Add(this.btnToggleEnabled);
            this.Controls.Add(this.lblTopText);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.HelpButton = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "HssMainForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "HookSpeechSharp (C) 2022 Caleb T.";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.HssMainForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Label lblTopText;
        private Button btnToggleEnabled;
        private Label lblAlphabetText;
        private TextBox tbxAlphabetChars;
        private GroupBox grpAlphabetDetails;
        private Button btnUpdateAlphabet;
    }
}