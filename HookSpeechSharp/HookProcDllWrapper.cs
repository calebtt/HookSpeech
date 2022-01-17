using System.Runtime.InteropServices;

namespace HookSpeechSharp
{
    public class HookProcDllWrapper
    {
        ~HookProcDllWrapper()
        {
            if (HookProcDllImports.IsHooked())
                HookProcDllImports.RemoveHooks();
        }

        public string GetTranslationAlphabet()
        {
            bool wasHooked = IsHooked();
            if (wasHooked)
                RemoveHooks();
            IntPtr p = HookProcDllImports.GetTranslationAlphabet();
            if (p != IntPtr.Zero)
            {
                string? retVal = Marshal.PtrToStringUni(p);
                if (wasHooked)
                    AddHooks();
                if (retVal != null)
                    return retVal;
                else
                    return String.Empty;
            }
            if (wasHooked)
                AddHooks();
            return String.Empty;
        }

        public bool SetTranslationAlphabet(string newAlphabet)
        {
            bool wasHooked = IsHooked();
            if (wasHooked)
                RemoveHooks();
            bool res = HookProcDllImports.SetTranslationAlphabet(newAlphabet);
            if (wasHooked)
                AddHooks();
            return res;
        }

        public string GetWorkingAlphabet()
        {
            IntPtr p = HookProcDllImports.GetWorkingAlphabet();
            if (p != IntPtr.Zero)
            {
                string? retVal = Marshal.PtrToStringAnsi(p);
                if (retVal != null)
                    return retVal;
                else
                    return String.Empty;
            }
            return String.Empty;
        }

        public bool IsHooked()
        {
            return HookProcDllImports.IsHooked();
        }

        public bool RemoveHooks()
        {
            return HookProcDllImports.RemoveHooks();
        }

        public bool AddHooks()
        {
            return HookProcDllImports.AddHooks();
        }
    }
}
