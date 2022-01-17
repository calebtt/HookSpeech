using System.Runtime.InteropServices;

namespace HookSpeechSharp
{
    public static class HookProcDllWrapper
    {
        public static string GetTranslationAlphabet()
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

        public static bool SetTranslationAlphabet(string newAlphabet)
        {
            bool wasHooked = IsHooked();
            if (wasHooked)
                RemoveHooks();
            bool res = HookProcDllImports.SetTranslationAlphabet(newAlphabet);
            if (wasHooked)
                AddHooks();
            return res;
        }

        public static string GetWorkingAlphabet()
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

        public static bool IsHooked()
        {
            return HookProcDllImports.IsHooked();
        }

        public static bool RemoveHooks()
        {
            return HookProcDllImports.RemoveHooks();
        }

        public static bool AddHooks()
        {
            return HookProcDllImports.AddHooks();
        }
    }
}
